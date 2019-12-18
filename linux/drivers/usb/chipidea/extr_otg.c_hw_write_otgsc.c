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
struct ci_hdrc_cable {int changed; int enabled; int /*<<< orphan*/  edev; } ;
struct ci_hdrc {scalar_t__ role_switch; TYPE_1__* platdata; } ;
struct TYPE_2__ {struct ci_hdrc_cable id_extcon; struct ci_hdrc_cable vbus_extcon; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OP_OTGSC ; 
 int OTGSC_BSVIE ; 
 int OTGSC_BSVIS ; 
 int OTGSC_IDIE ; 
 int OTGSC_IDIS ; 
 int OTGSC_INT_STATUS_BITS ; 
 int /*<<< orphan*/  hw_write (struct ci_hdrc*,int /*<<< orphan*/ ,int,int) ; 

void hw_write_otgsc(struct ci_hdrc *ci, u32 mask, u32 data)
{
	struct ci_hdrc_cable *cable;

	cable = &ci->platdata->vbus_extcon;
	if (!IS_ERR(cable->edev) || ci->role_switch) {
		if (data & mask & OTGSC_BSVIS)
			cable->changed = false;

		/* Don't enable vbus interrupt if using external notifier */
		if (data & mask & OTGSC_BSVIE) {
			cable->enabled = true;
			data &= ~OTGSC_BSVIE;
		} else if (mask & OTGSC_BSVIE) {
			cable->enabled = false;
		}
	}

	cable = &ci->platdata->id_extcon;
	if (!IS_ERR(cable->edev) || ci->role_switch) {
		if (data & mask & OTGSC_IDIS)
			cable->changed = false;

		/* Don't enable id interrupt if using external notifier */
		if (data & mask & OTGSC_IDIE) {
			cable->enabled = true;
			data &= ~OTGSC_IDIE;
		} else if (mask & OTGSC_IDIE) {
			cable->enabled = false;
		}
	}

	hw_write(ci, OP_OTGSC, mask | OTGSC_INT_STATUS_BITS, data);
}