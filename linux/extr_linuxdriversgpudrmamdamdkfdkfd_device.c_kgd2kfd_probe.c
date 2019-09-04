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
struct pci_dev {int /*<<< orphan*/  device; int /*<<< orphan*/  vendor; } ;
struct kgd_dev {int dummy; } ;
struct kfd_device_info {scalar_t__ needs_pci_atomics; } ;
struct kfd_dev {int init_complete; int /*<<< orphan*/  doorbell_available_index; int /*<<< orphan*/  doorbell_mutex; struct kfd2kgd_calls const* kfd2kgd; struct pci_dev* pdev; struct kfd_device_info const* device_info; struct kgd_dev* kgd; } ;
struct kfd2kgd_calls {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PCI_EXP_DEVCAP2_ATOMIC_COMP32 ; 
 int PCI_EXP_DEVCAP2_ATOMIC_COMP64 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfd_device ; 
 struct kfd_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct kfd_device_info* lookup_device_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int pci_enable_atomic_ops_to_root (struct pci_dev*,int) ; 

struct kfd_dev *kgd2kfd_probe(struct kgd_dev *kgd,
	struct pci_dev *pdev, const struct kfd2kgd_calls *f2g)
{
	struct kfd_dev *kfd;
	int ret;
	const struct kfd_device_info *device_info =
					lookup_device_info(pdev->device);

	if (!device_info) {
		dev_err(kfd_device, "kgd2kfd_probe failed\n");
		return NULL;
	}

	/* Allow BIF to recode atomics to PCIe 3.0 AtomicOps.
	 * 32 and 64-bit requests are possible and must be
	 * supported.
	 */
	ret = pci_enable_atomic_ops_to_root(pdev,
			PCI_EXP_DEVCAP2_ATOMIC_COMP32 |
			PCI_EXP_DEVCAP2_ATOMIC_COMP64);
	if (device_info->needs_pci_atomics && ret < 0) {
		dev_info(kfd_device,
			 "skipped device %x:%x, PCI rejects atomics\n",
			 pdev->vendor, pdev->device);
		return NULL;
	}

	kfd = kzalloc(sizeof(*kfd), GFP_KERNEL);
	if (!kfd)
		return NULL;

	kfd->kgd = kgd;
	kfd->device_info = device_info;
	kfd->pdev = pdev;
	kfd->init_complete = false;
	kfd->kfd2kgd = f2g;

	mutex_init(&kfd->doorbell_mutex);
	memset(&kfd->doorbell_available_index, 0,
		sizeof(kfd->doorbell_available_index));

	return kfd;
}