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
struct tg3 {int /*<<< orphan*/  dev; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_D0 ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int pci_set_power_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tg3_enable_register_access (struct tg3*) ; 
 int /*<<< orphan*/  tg3_pwrsrc_switch_to_vmain (struct tg3*) ; 

__attribute__((used)) static int tg3_power_up(struct tg3 *tp)
{
	int err;

	tg3_enable_register_access(tp);

	err = pci_set_power_state(tp->pdev, PCI_D0);
	if (!err) {
		/* Switch out of Vaux if it is a NIC */
		tg3_pwrsrc_switch_to_vmain(tp);
	} else {
		netdev_err(tp->dev, "Transition to D0 failed\n");
	}

	return err;
}