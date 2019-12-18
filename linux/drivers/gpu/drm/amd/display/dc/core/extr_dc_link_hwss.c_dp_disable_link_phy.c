#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct dmcu {TYPE_7__* funcs; } ;
struct TYPE_12__ {int /*<<< orphan*/  dp_keep_receiver_powered; } ;
struct dc_link {int /*<<< orphan*/  cur_link_settings; TYPE_8__* link_enc; TYPE_5__* dc; TYPE_3__ wa_flags; TYPE_1__* ctx; } ;
struct dc {TYPE_2__* res_pool; } ;
typedef  enum signal_type { ____Placeholder_signal_type } signal_type ;
struct TYPE_17__ {TYPE_6__* funcs; } ;
struct TYPE_16__ {int /*<<< orphan*/  (* unlock_phy ) (struct dmcu*) ;int /*<<< orphan*/  (* lock_phy ) (struct dmcu*) ;} ;
struct TYPE_15__ {int /*<<< orphan*/  (* disable_output ) (TYPE_8__*,int) ;} ;
struct TYPE_13__ {int /*<<< orphan*/  (* edp_power_control ) (struct dc_link*,int) ;} ;
struct TYPE_14__ {TYPE_4__ hwss; } ;
struct TYPE_11__ {struct dmcu* dmcu; } ;
struct TYPE_10__ {struct dc* dc; } ;

/* Variables and functions */
 int SIGNAL_TYPE_EDP ; 
 int /*<<< orphan*/  dp_receiver_power_ctrl (struct dc_link*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_8__*,int) ; 
 int /*<<< orphan*/  stub2 (struct dc_link*,int) ; 
 int /*<<< orphan*/  stub3 (struct dmcu*) ; 
 int /*<<< orphan*/  stub4 (TYPE_8__*,int) ; 
 int /*<<< orphan*/  stub5 (struct dmcu*) ; 

void dp_disable_link_phy(struct dc_link *link, enum signal_type signal)
{
	struct dc  *core_dc = link->ctx->dc;
	struct dmcu *dmcu = core_dc->res_pool->dmcu;

	if (!link->wa_flags.dp_keep_receiver_powered)
		dp_receiver_power_ctrl(link, false);

	if (signal == SIGNAL_TYPE_EDP) {
		link->link_enc->funcs->disable_output(link->link_enc, signal);
		link->dc->hwss.edp_power_control(link, false);
	} else {
		if (dmcu != NULL && dmcu->funcs->lock_phy)
			dmcu->funcs->lock_phy(dmcu);

		link->link_enc->funcs->disable_output(link->link_enc, signal);

		if (dmcu != NULL && dmcu->funcs->unlock_phy)
			dmcu->funcs->unlock_phy(dmcu);
	}

	/* Clear current link setting.*/
	memset(&link->cur_link_settings, 0,
			sizeof(link->cur_link_settings));
}