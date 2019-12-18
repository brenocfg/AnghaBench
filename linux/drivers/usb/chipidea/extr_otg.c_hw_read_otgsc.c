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
typedef  int u32 ;
struct ci_hdrc_cable {scalar_t__ enabled; scalar_t__ connected; scalar_t__ changed; int /*<<< orphan*/  edev; } ;
struct ci_hdrc {scalar_t__ role_switch; TYPE_1__* platdata; } ;
struct TYPE_2__ {struct ci_hdrc_cable id_extcon; struct ci_hdrc_cable vbus_extcon; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OP_OTGSC ; 
 int OTGSC_BSV ; 
 int OTGSC_BSVIE ; 
 int OTGSC_BSVIS ; 
 int OTGSC_ID ; 
 int OTGSC_IDIE ; 
 int OTGSC_IDIS ; 
 int hw_read (struct ci_hdrc*,int /*<<< orphan*/ ,int) ; 

u32 hw_read_otgsc(struct ci_hdrc *ci, u32 mask)
{
	struct ci_hdrc_cable *cable;
	u32 val = hw_read(ci, OP_OTGSC, mask);

	/*
	 * If using extcon framework for VBUS and/or ID signal
	 * detection overwrite OTGSC register value
	 */
	cable = &ci->platdata->vbus_extcon;
	if (!IS_ERR(cable->edev) || ci->role_switch) {
		if (cable->changed)
			val |= OTGSC_BSVIS;
		else
			val &= ~OTGSC_BSVIS;

		if (cable->connected)
			val |= OTGSC_BSV;
		else
			val &= ~OTGSC_BSV;

		if (cable->enabled)
			val |= OTGSC_BSVIE;
		else
			val &= ~OTGSC_BSVIE;
	}

	cable = &ci->platdata->id_extcon;
	if (!IS_ERR(cable->edev) || ci->role_switch) {
		if (cable->changed)
			val |= OTGSC_IDIS;
		else
			val &= ~OTGSC_IDIS;

		if (cable->connected)
			val &= ~OTGSC_ID; /* host */
		else
			val |= OTGSC_ID; /* device */

		if (cable->enabled)
			val |= OTGSC_IDIE;
		else
			val &= ~OTGSC_IDIE;
	}

	return val & mask;
}