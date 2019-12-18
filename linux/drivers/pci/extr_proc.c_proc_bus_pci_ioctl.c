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
struct pci_filp_private {int write_combine; int /*<<< orphan*/  mmap_state; } ;
struct pci_dev {int /*<<< orphan*/  bus; } ;
struct file {struct pci_filp_private* private_data; } ;

/* Variables and functions */
 long EINVAL ; 
 int /*<<< orphan*/  LOCKDOWN_PCI_ACCESS ; 
#define  PCIIOC_CONTROLLER 131 
#define  PCIIOC_MMAP_IS_IO 130 
#define  PCIIOC_MMAP_IS_MEM 129 
#define  PCIIOC_WRITE_COMBINE 128 
 struct pci_dev* PDE_DATA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arch_can_pci_mmap_io () ; 
 int /*<<< orphan*/  arch_can_pci_mmap_wc () ; 
 int /*<<< orphan*/  file_inode (struct file*) ; 
 int pci_domain_nr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_mmap_io ; 
 int /*<<< orphan*/  pci_mmap_mem ; 
 int security_locked_down (int /*<<< orphan*/ ) ; 

__attribute__((used)) static long proc_bus_pci_ioctl(struct file *file, unsigned int cmd,
			       unsigned long arg)
{
	struct pci_dev *dev = PDE_DATA(file_inode(file));
#ifdef HAVE_PCI_MMAP
	struct pci_filp_private *fpriv = file->private_data;
#endif /* HAVE_PCI_MMAP */
	int ret = 0;

	ret = security_locked_down(LOCKDOWN_PCI_ACCESS);
	if (ret)
		return ret;

	switch (cmd) {
	case PCIIOC_CONTROLLER:
		ret = pci_domain_nr(dev->bus);
		break;

#ifdef HAVE_PCI_MMAP
	case PCIIOC_MMAP_IS_IO:
		if (!arch_can_pci_mmap_io())
			return -EINVAL;
		fpriv->mmap_state = pci_mmap_io;
		break;

	case PCIIOC_MMAP_IS_MEM:
		fpriv->mmap_state = pci_mmap_mem;
		break;

	case PCIIOC_WRITE_COMBINE:
		if (arch_can_pci_mmap_wc()) {
			if (arg)
				fpriv->write_combine = 1;
			else
				fpriv->write_combine = 0;
			break;
		}
		/* If arch decided it can't, fall through... */
#endif /* HAVE_PCI_MMAP */
		/* fall through */
	default:
		ret = -EINVAL;
		break;
	}

	return ret;
}