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
union power_supply_propval {int /*<<< orphan*/  intval; } ;
struct TYPE_2__ {scalar_t__ active; } ;
struct tcpm_port {TYPE_1__ pps_data; scalar_t__ vbus_charge; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCPM_PSY_FIXED_ONLINE ; 
 int /*<<< orphan*/  TCPM_PSY_OFFLINE ; 
 int /*<<< orphan*/  TCPM_PSY_PROG_ONLINE ; 

__attribute__((used)) static int tcpm_psy_get_online(struct tcpm_port *port,
			       union power_supply_propval *val)
{
	if (port->vbus_charge) {
		if (port->pps_data.active)
			val->intval = TCPM_PSY_PROG_ONLINE;
		else
			val->intval = TCPM_PSY_FIXED_ONLINE;
	} else {
		val->intval = TCPM_PSY_OFFLINE;
	}

	return 0;
}