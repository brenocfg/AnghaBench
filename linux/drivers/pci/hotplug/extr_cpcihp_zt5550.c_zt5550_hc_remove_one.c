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

/* Variables and functions */
 int /*<<< orphan*/  bus0 ; 
 int /*<<< orphan*/  cpci_hp_stop () ; 
 int /*<<< orphan*/  cpci_hp_unregister_bus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpci_hp_unregister_controller (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zt5550_hc_cleanup () ; 
 int /*<<< orphan*/  zt5550_hpc ; 

__attribute__((used)) static void zt5550_hc_remove_one(struct pci_dev *pdev)
{
	cpci_hp_stop();
	cpci_hp_unregister_bus(bus0);
	cpci_hp_unregister_controller(&zt5550_hpc);
	zt5550_hc_cleanup();
}