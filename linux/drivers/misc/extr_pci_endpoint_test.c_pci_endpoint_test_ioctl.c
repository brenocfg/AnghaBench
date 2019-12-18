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
struct pci_endpoint_test {int /*<<< orphan*/  mutex; struct pci_dev* pdev; } ;
struct pci_dev {int dummy; } ;
struct file {int /*<<< orphan*/  private_data; } ;
typedef  enum pci_barno { ____Placeholder_pci_barno } pci_barno ;

/* Variables and functions */
 int BAR_0 ; 
 int EINVAL ; 
#define  PCITEST_BAR 136 
#define  PCITEST_COPY 135 
#define  PCITEST_GET_IRQTYPE 134 
#define  PCITEST_LEGACY_IRQ 133 
#define  PCITEST_MSI 132 
#define  PCITEST_MSIX 131 
#define  PCITEST_READ 130 
#define  PCITEST_SET_IRQTYPE 129 
#define  PCITEST_WRITE 128 
 int irq_type ; 
 int /*<<< orphan*/  is_am654_pci_dev (struct pci_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pci_endpoint_test_bar (struct pci_endpoint_test*,int) ; 
 int pci_endpoint_test_copy (struct pci_endpoint_test*,unsigned long) ; 
 int pci_endpoint_test_legacy_irq (struct pci_endpoint_test*) ; 
 int pci_endpoint_test_msi_irq (struct pci_endpoint_test*,unsigned long,int) ; 
 int pci_endpoint_test_read (struct pci_endpoint_test*,unsigned long) ; 
 int pci_endpoint_test_set_irq (struct pci_endpoint_test*,unsigned long) ; 
 int pci_endpoint_test_write (struct pci_endpoint_test*,unsigned long) ; 
 struct pci_endpoint_test* to_endpoint_test (int /*<<< orphan*/ ) ; 

__attribute__((used)) static long pci_endpoint_test_ioctl(struct file *file, unsigned int cmd,
				    unsigned long arg)
{
	int ret = -EINVAL;
	enum pci_barno bar;
	struct pci_endpoint_test *test = to_endpoint_test(file->private_data);
	struct pci_dev *pdev = test->pdev;

	mutex_lock(&test->mutex);
	switch (cmd) {
	case PCITEST_BAR:
		bar = arg;
		if (bar < 0 || bar > 5)
			goto ret;
		if (is_am654_pci_dev(pdev) && bar == BAR_0)
			goto ret;
		ret = pci_endpoint_test_bar(test, bar);
		break;
	case PCITEST_LEGACY_IRQ:
		ret = pci_endpoint_test_legacy_irq(test);
		break;
	case PCITEST_MSI:
	case PCITEST_MSIX:
		ret = pci_endpoint_test_msi_irq(test, arg, cmd == PCITEST_MSIX);
		break;
	case PCITEST_WRITE:
		ret = pci_endpoint_test_write(test, arg);
		break;
	case PCITEST_READ:
		ret = pci_endpoint_test_read(test, arg);
		break;
	case PCITEST_COPY:
		ret = pci_endpoint_test_copy(test, arg);
		break;
	case PCITEST_SET_IRQTYPE:
		ret = pci_endpoint_test_set_irq(test, arg);
		break;
	case PCITEST_GET_IRQTYPE:
		ret = irq_type;
		break;
	}

ret:
	mutex_unlock(&test->mutex);
	return ret;
}