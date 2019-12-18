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
struct eeepc_laptop {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CM_ASL_WLAN ; 
 int get_acpi (struct eeepc_laptop*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool eeepc_wlan_rfkill_blocked(struct eeepc_laptop *eeepc)
{
	if (get_acpi(eeepc, CM_ASL_WLAN) == 1)
		return false;
	return true;
}