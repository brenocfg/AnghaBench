#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct vfio_pci_device {int /*<<< orphan*/  ioeventfds_list; int /*<<< orphan*/  ioeventfds_lock; int /*<<< orphan*/  irqlock; int /*<<< orphan*/  igate; int /*<<< orphan*/  irq_type; struct pci_dev* pdev; } ;
struct pci_device_id {int dummy; } ;
struct pci_dev {scalar_t__ hdr_type; int /*<<< orphan*/  dev; } ;
struct iommu_group {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PCI_D0 ; 
 int /*<<< orphan*/  PCI_D3hot ; 
 scalar_t__ PCI_HEADER_TYPE_NORMAL ; 
 int /*<<< orphan*/  VFIO_PCI_NUM_IRQS ; 
 int /*<<< orphan*/  disable_idle_d3 ; 
 int /*<<< orphan*/  kfree (struct vfio_pci_device*) ; 
 struct vfio_pci_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 scalar_t__ pci_num_vf (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_warn (struct pci_dev*,char*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int vfio_add_group_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct vfio_pci_device*) ; 
 int /*<<< orphan*/  vfio_del_group_dev (int /*<<< orphan*/ *) ; 
 struct iommu_group* vfio_iommu_group_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfio_iommu_group_put (struct iommu_group*,int /*<<< orphan*/ *) ; 
 scalar_t__ vfio_pci_is_vga (struct pci_dev*) ; 
 int /*<<< orphan*/  vfio_pci_ops ; 
 int /*<<< orphan*/  vfio_pci_probe_power_state (struct vfio_pci_device*) ; 
 int vfio_pci_reflck_attach (struct vfio_pci_device*) ; 
 int /*<<< orphan*/  vfio_pci_set_power_state (struct vfio_pci_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfio_pci_set_vga_decode (struct vfio_pci_device*,int) ; 
 int /*<<< orphan*/  vga_client_register (struct pci_dev*,struct vfio_pci_device*,int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (struct vfio_pci_device*,int)) ; 
 int /*<<< orphan*/  vga_set_legacy_decoding (struct pci_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vfio_pci_probe(struct pci_dev *pdev, const struct pci_device_id *id)
{
	struct vfio_pci_device *vdev;
	struct iommu_group *group;
	int ret;

	if (pdev->hdr_type != PCI_HEADER_TYPE_NORMAL)
		return -EINVAL;

	/*
	 * Prevent binding to PFs with VFs enabled, this too easily allows
	 * userspace instance with VFs and PFs from the same device, which
	 * cannot work.  Disabling SR-IOV here would initiate removing the
	 * VFs, which would unbind the driver, which is prone to blocking
	 * if that VF is also in use by vfio-pci.  Just reject these PFs
	 * and let the user sort it out.
	 */
	if (pci_num_vf(pdev)) {
		pci_warn(pdev, "Cannot bind to PF with SR-IOV enabled\n");
		return -EBUSY;
	}

	group = vfio_iommu_group_get(&pdev->dev);
	if (!group)
		return -EINVAL;

	vdev = kzalloc(sizeof(*vdev), GFP_KERNEL);
	if (!vdev) {
		vfio_iommu_group_put(group, &pdev->dev);
		return -ENOMEM;
	}

	vdev->pdev = pdev;
	vdev->irq_type = VFIO_PCI_NUM_IRQS;
	mutex_init(&vdev->igate);
	spin_lock_init(&vdev->irqlock);
	mutex_init(&vdev->ioeventfds_lock);
	INIT_LIST_HEAD(&vdev->ioeventfds_list);

	ret = vfio_add_group_dev(&pdev->dev, &vfio_pci_ops, vdev);
	if (ret) {
		vfio_iommu_group_put(group, &pdev->dev);
		kfree(vdev);
		return ret;
	}

	ret = vfio_pci_reflck_attach(vdev);
	if (ret) {
		vfio_del_group_dev(&pdev->dev);
		vfio_iommu_group_put(group, &pdev->dev);
		kfree(vdev);
		return ret;
	}

	if (vfio_pci_is_vga(pdev)) {
		vga_client_register(pdev, vdev, NULL, vfio_pci_set_vga_decode);
		vga_set_legacy_decoding(pdev,
					vfio_pci_set_vga_decode(vdev, false));
	}

	vfio_pci_probe_power_state(vdev);

	if (!disable_idle_d3) {
		/*
		 * pci-core sets the device power state to an unknown value at
		 * bootup and after being removed from a driver.  The only
		 * transition it allows from this unknown state is to D0, which
		 * typically happens when a driver calls pci_enable_device().
		 * We're not ready to enable the device yet, but we do want to
		 * be able to get to D3.  Therefore first do a D0 transition
		 * before going to D3.
		 */
		vfio_pci_set_power_state(vdev, PCI_D0);
		vfio_pci_set_power_state(vdev, PCI_D3hot);
	}

	return ret;
}