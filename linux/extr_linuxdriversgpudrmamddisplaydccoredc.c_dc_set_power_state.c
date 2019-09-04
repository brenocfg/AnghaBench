#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct kref {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* power_down ) (struct dc*) ;int /*<<< orphan*/  (* init_hw ) (struct dc*) ;} ;
struct dc {TYPE_2__* current_state; TYPE_1__ hwss; } ;
typedef  enum dc_acpi_cm_power_state { ____Placeholder_dc_acpi_cm_power_state } dc_acpi_cm_power_state ;
struct TYPE_6__ {struct kref refcount; } ;

/* Variables and functions */
#define  DC_ACPI_CM_POWER_STATE_D0 128 
 int /*<<< orphan*/  dc_resource_state_construct (struct dc*,TYPE_2__*) ; 
 int /*<<< orphan*/  dc_resource_state_destruct (TYPE_2__*) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct dc*) ; 
 int /*<<< orphan*/  stub2 (struct dc*) ; 

void dc_set_power_state(
	struct dc *dc,
	enum dc_acpi_cm_power_state power_state)
{
	struct kref refcount;

	switch (power_state) {
	case DC_ACPI_CM_POWER_STATE_D0:
		dc_resource_state_construct(dc, dc->current_state);

		dc->hwss.init_hw(dc);
		break;
	default:

		dc->hwss.power_down(dc);

		/* Zero out the current context so that on resume we start with
		 * clean state, and dc hw programming optimizations will not
		 * cause any trouble.
		 */

		/* Preserve refcount */
		refcount = dc->current_state->refcount;
		dc_resource_state_destruct(dc->current_state);
		memset(dc->current_state, 0,
				sizeof(*dc->current_state));

		dc->current_state->refcount = refcount;

		break;
	}

}