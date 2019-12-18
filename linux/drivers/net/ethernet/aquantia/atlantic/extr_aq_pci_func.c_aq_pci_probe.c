#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct net_device {int dummy; } ;
struct aq_nic_s {int irqvecs; TYPE_1__* aq_hw; struct pci_dev* pdev; int /*<<< orphan*/  aq_hw_ops; int /*<<< orphan*/  fwreq_mutex; } ;
typedef  unsigned int resource_size_t ;
struct TYPE_7__ {TYPE_3__* aq_hw_caps; } ;
struct TYPE_6__ {int /*<<< orphan*/  msix_irqs; } ;
struct TYPE_5__ {int /*<<< orphan*/  mmio; TYPE_4__* aq_nic_cfg; } ;

/* Variables and functions */
 scalar_t__ AQ_CFG_VECS_DEF ; 
 scalar_t__ AQ_HW_SERVICE_IRQS ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IORESOURCE_MEM ; 
 int PCI_IRQ_LEGACY ; 
 int PCI_IRQ_MSI ; 
 int PCI_IRQ_MSIX ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aq_drvinfo_init (struct net_device*) ; 
 struct net_device* aq_ndev_alloc () ; 
 int /*<<< orphan*/  aq_nic_cfg_start (struct aq_nic_s*) ; 
 int /*<<< orphan*/  aq_nic_free_vectors (struct aq_nic_s*) ; 
 TYPE_4__* aq_nic_get_cfg (struct aq_nic_s*) ; 
 int /*<<< orphan*/  aq_nic_ndev_init (struct aq_nic_s*) ; 
 int aq_nic_ndev_register (struct aq_nic_s*) ; 
 int /*<<< orphan*/  aq_pci_free_irq_vectors (struct aq_nic_s*) ; 
 int aq_pci_func_init (struct pci_dev*) ; 
 int aq_pci_probe_get_hw_by_id (struct pci_dev*,int /*<<< orphan*/ *,TYPE_3__**) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  ioremap_nocache (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 TYPE_1__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int min (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct aq_nic_s* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  num_online_cpus () ; 
 int pci_alloc_irq_vectors (struct pci_dev*,int,int,int) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int pci_resource_flags (struct pci_dev*,int) ; 
 unsigned int pci_resource_len (struct pci_dev*,int) ; 
 unsigned int pci_resource_start (struct pci_dev*,int) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct aq_nic_s*) ; 

__attribute__((used)) static int aq_pci_probe(struct pci_dev *pdev,
			const struct pci_device_id *pci_id)
{
	struct aq_nic_s *self;
	int err;
	struct net_device *ndev;
	resource_size_t mmio_pa;
	u32 bar;
	u32 numvecs;

	err = pci_enable_device(pdev);
	if (err)
		return err;

	err = aq_pci_func_init(pdev);
	if (err)
		goto err_pci_func;

	ndev = aq_ndev_alloc();
	if (!ndev) {
		err = -ENOMEM;
		goto err_ndev;
	}

	self = netdev_priv(ndev);
	self->pdev = pdev;
	SET_NETDEV_DEV(ndev, &pdev->dev);
	pci_set_drvdata(pdev, self);

	mutex_init(&self->fwreq_mutex);

	err = aq_pci_probe_get_hw_by_id(pdev, &self->aq_hw_ops,
					&aq_nic_get_cfg(self)->aq_hw_caps);
	if (err)
		goto err_ioremap;

	self->aq_hw = kzalloc(sizeof(*self->aq_hw), GFP_KERNEL);
	if (!self->aq_hw) {
		err = -ENOMEM;
		goto err_ioremap;
	}
	self->aq_hw->aq_nic_cfg = aq_nic_get_cfg(self);

	for (bar = 0; bar < 4; ++bar) {
		if (IORESOURCE_MEM & pci_resource_flags(pdev, bar)) {
			resource_size_t reg_sz;

			mmio_pa = pci_resource_start(pdev, bar);
			if (mmio_pa == 0U) {
				err = -EIO;
				goto err_free_aq_hw;
			}

			reg_sz = pci_resource_len(pdev, bar);
			if ((reg_sz <= 24 /*ATL_REGS_SIZE*/)) {
				err = -EIO;
				goto err_free_aq_hw;
			}

			self->aq_hw->mmio = ioremap_nocache(mmio_pa, reg_sz);
			if (!self->aq_hw->mmio) {
				err = -EIO;
				goto err_free_aq_hw;
			}
			break;
		}
	}

	if (bar == 4) {
		err = -EIO;
		goto err_free_aq_hw;
	}

	numvecs = min((u8)AQ_CFG_VECS_DEF,
		      aq_nic_get_cfg(self)->aq_hw_caps->msix_irqs);
	numvecs = min(numvecs, num_online_cpus());
	numvecs += AQ_HW_SERVICE_IRQS;
	/*enable interrupts */
#if !AQ_CFG_FORCE_LEGACY_INT
	err = pci_alloc_irq_vectors(self->pdev, 1, numvecs,
				    PCI_IRQ_MSIX | PCI_IRQ_MSI |
				    PCI_IRQ_LEGACY);

	if (err < 0)
		goto err_hwinit;
	numvecs = err;
#endif
	self->irqvecs = numvecs;

	/* net device init */
	aq_nic_cfg_start(self);

	aq_nic_ndev_init(self);

	err = aq_nic_ndev_register(self);
	if (err < 0)
		goto err_register;

	aq_drvinfo_init(ndev);

	return 0;

err_register:
	aq_nic_free_vectors(self);
	aq_pci_free_irq_vectors(self);
err_hwinit:
	iounmap(self->aq_hw->mmio);
err_free_aq_hw:
	kfree(self->aq_hw);
err_ioremap:
	free_netdev(ndev);
err_ndev:
	pci_release_regions(pdev);
err_pci_func:
	pci_disable_device(pdev);
	return err;
}