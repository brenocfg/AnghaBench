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
struct pti_dev {int /*<<< orphan*/  pti_ioaddr; int /*<<< orphan*/ * port; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 unsigned int PTITTY_MINOR_NUM ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct pti_dev*) ; 
 int /*<<< orphan*/  misc_deregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct pti_dev* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_region (struct pci_dev*,int) ; 
 int /*<<< orphan*/  pti_char_driver ; 
 int /*<<< orphan*/  pti_console ; 
 int /*<<< orphan*/  pti_tty_driver ; 
 int /*<<< orphan*/  tty_port_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_unregister_device (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  unregister_console (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pti_pci_remove(struct pci_dev *pdev)
{
	struct pti_dev *drv_data = pci_get_drvdata(pdev);
	unsigned int a;

	unregister_console(&pti_console);

	for (a = 0; a < PTITTY_MINOR_NUM; a++) {
		tty_unregister_device(pti_tty_driver, a);
		tty_port_destroy(&drv_data->port[a]);
	}

	iounmap(drv_data->pti_ioaddr);
	kfree(drv_data);
	pci_release_region(pdev, 1);
	pci_disable_device(pdev);

	misc_deregister(&pti_char_driver);
}