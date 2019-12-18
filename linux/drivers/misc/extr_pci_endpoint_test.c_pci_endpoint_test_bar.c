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
typedef  int u32 ;
struct pci_endpoint_test {int test_reg_bar; int /*<<< orphan*/ * bar; struct pci_dev* pdev; } ;
struct pci_dev {int dummy; } ;
typedef  enum pci_barno { ____Placeholder_pci_barno } pci_barno ;

/* Variables and functions */
 int pci_endpoint_test_bar_readl (struct pci_endpoint_test*,int,int) ; 
 int /*<<< orphan*/  pci_endpoint_test_bar_writel (struct pci_endpoint_test*,int,int,int) ; 
 int pci_resource_len (struct pci_dev*,int) ; 

__attribute__((used)) static bool pci_endpoint_test_bar(struct pci_endpoint_test *test,
				  enum pci_barno barno)
{
	int j;
	u32 val;
	int size;
	struct pci_dev *pdev = test->pdev;

	if (!test->bar[barno])
		return false;

	size = pci_resource_len(pdev, barno);

	if (barno == test->test_reg_bar)
		size = 0x4;

	for (j = 0; j < size; j += 4)
		pci_endpoint_test_bar_writel(test, barno, j, 0xA0A0A0A0);

	for (j = 0; j < size; j += 4) {
		val = pci_endpoint_test_bar_readl(test, barno, j);
		if (val != 0xA0A0A0A0)
			return false;
	}

	return true;
}