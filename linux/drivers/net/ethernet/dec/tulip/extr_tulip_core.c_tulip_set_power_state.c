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
struct tulip_private {int flags; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFDD ; 
 int CFDD_Sleep ; 
 int CFDD_Snooze ; 
 int HAS_ACPI ; 
 int /*<<< orphan*/  pci_read_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_write_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void tulip_set_power_state (struct tulip_private *tp,
				   int sleep, int snooze)
{
	if (tp->flags & HAS_ACPI) {
		u32 tmp, newtmp;
		pci_read_config_dword (tp->pdev, CFDD, &tmp);
		newtmp = tmp & ~(CFDD_Sleep | CFDD_Snooze);
		if (sleep)
			newtmp |= CFDD_Sleep;
		else if (snooze)
			newtmp |= CFDD_Snooze;
		if (tmp != newtmp)
			pci_write_config_dword (tp->pdev, CFDD, newtmp);
	}

}