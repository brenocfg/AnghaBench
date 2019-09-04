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
struct pci_dev {int dummy; } ;
struct cobalt {int /*<<< orphan*/ * bar1; int /*<<< orphan*/ * bar0; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_iounmap (struct pci_dev*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cobalt_pci_iounmap(struct cobalt *cobalt, struct pci_dev *pci_dev)
{
	if (cobalt->bar0) {
		pci_iounmap(pci_dev, cobalt->bar0);
		cobalt->bar0 = NULL;
	}
	if (cobalt->bar1) {
		pci_iounmap(pci_dev, cobalt->bar1);
		cobalt->bar1 = NULL;
	}
}