#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  vbus_drop_end; } ;
struct ab8500_charger {TYPE_1__ flags; } ;

/* Variables and functions */
 int AB8500_USBCH_IPT_CRNTLVL_REG ; 

__attribute__((used)) static bool ab8500_charger_check_continue_stepping(struct ab8500_charger *di,
						   int reg)
{
	if (reg == AB8500_USBCH_IPT_CRNTLVL_REG)
		return !di->flags.vbus_drop_end;
	else
		return true;
}