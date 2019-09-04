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
struct mantis_pci {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct mantis_pci*) ; 
 int /*<<< orphan*/  mantis_dma_exit (struct mantis_pci*) ; 
 int /*<<< orphan*/  mantis_dvb_exit (struct mantis_pci*) ; 
 int /*<<< orphan*/  mantis_i2c_exit (struct mantis_pci*) ; 
 int /*<<< orphan*/  mantis_input_exit (struct mantis_pci*) ; 
 int /*<<< orphan*/  mantis_pci_exit (struct mantis_pci*) ; 
 int /*<<< orphan*/  mantis_uart_exit (struct mantis_pci*) ; 
 struct mantis_pci* pci_get_drvdata (struct pci_dev*) ; 

__attribute__((used)) static void mantis_pci_remove(struct pci_dev *pdev)
{
	struct mantis_pci *mantis = pci_get_drvdata(pdev);

	if (mantis) {

		mantis_uart_exit(mantis);
		mantis_input_exit(mantis);
		mantis_dvb_exit(mantis);
		mantis_dma_exit(mantis);
		mantis_i2c_exit(mantis);
		mantis_pci_exit(mantis);
		kfree(mantis);
	}
	return;
}