#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct kref {int dummy; } ;
struct display_mode_lib {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  valid; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* init_sys_ctx ) (int /*<<< orphan*/ ,struct dc*,TYPE_3__*) ;int /*<<< orphan*/  (* init_hw ) (struct dc*) ;} ;
struct dc {TYPE_4__* current_state; TYPE_3__ vm_pa_config; int /*<<< orphan*/  hwseq; TYPE_1__ hwss; } ;
typedef  enum dc_acpi_cm_power_state { ____Placeholder_dc_acpi_cm_power_state } dc_acpi_cm_power_state ;
struct TYPE_8__ {struct display_mode_lib dml; } ;
struct TYPE_10__ {TYPE_2__ bw_ctx; struct kref refcount; int /*<<< orphan*/  stream_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
#define  DC_ACPI_CM_POWER_STATE_D0 128 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dc_resource_state_construct (struct dc*,TYPE_4__*) ; 
 int /*<<< orphan*/  dc_resource_state_destruct (TYPE_4__*) ; 
 int /*<<< orphan*/  kfree (struct display_mode_lib*) ; 
 struct display_mode_lib* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct display_mode_lib*,struct display_mode_lib*,int) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct dc*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,struct dc*,TYPE_3__*) ; 

void dc_set_power_state(
	struct dc *dc,
	enum dc_acpi_cm_power_state power_state)
{
	struct kref refcount;
	struct display_mode_lib *dml = kzalloc(sizeof(struct display_mode_lib),
						GFP_KERNEL);

	ASSERT(dml);
	if (!dml)
		return;

	switch (power_state) {
	case DC_ACPI_CM_POWER_STATE_D0:
		dc_resource_state_construct(dc, dc->current_state);

		dc->hwss.init_hw(dc);

#ifdef CONFIG_DRM_AMD_DC_DCN2_0
		if (dc->hwss.init_sys_ctx != NULL &&
			dc->vm_pa_config.valid) {
			dc->hwss.init_sys_ctx(dc->hwseq, dc, &dc->vm_pa_config);
		}
#endif

		break;
	default:
		ASSERT(dc->current_state->stream_count == 0);
		/* Zero out the current context so that on resume we start with
		 * clean state, and dc hw programming optimizations will not
		 * cause any trouble.
		 */

		/* Preserve refcount */
		refcount = dc->current_state->refcount;
		/* Preserve display mode lib */
		memcpy(dml, &dc->current_state->bw_ctx.dml, sizeof(struct display_mode_lib));

		dc_resource_state_destruct(dc->current_state);
		memset(dc->current_state, 0,
				sizeof(*dc->current_state));

		dc->current_state->refcount = refcount;
		dc->current_state->bw_ctx.dml = *dml;

		break;
	}

	kfree(dml);
}