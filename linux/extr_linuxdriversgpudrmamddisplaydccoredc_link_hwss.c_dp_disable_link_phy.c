#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  dp_keep_receiver_powered; } ;
struct dc_link {int /*<<< orphan*/  cur_link_settings; TYPE_5__* link_enc; TYPE_2__* dc; TYPE_3__ wa_flags; } ;
typedef  enum signal_type { ____Placeholder_signal_type } signal_type ;
struct TYPE_11__ {TYPE_4__* funcs; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* disable_output ) (TYPE_5__*,int) ;} ;
struct TYPE_7__ {int /*<<< orphan*/  (* edp_power_control ) (struct dc_link*,int) ;} ;
struct TYPE_8__ {TYPE_1__ hwss; } ;

/* Variables and functions */
 int SIGNAL_TYPE_EDP ; 
 int /*<<< orphan*/  dp_receiver_power_ctrl (struct dc_link*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*,int) ; 
 int /*<<< orphan*/  stub2 (struct dc_link*,int) ; 
 int /*<<< orphan*/  stub3 (TYPE_5__*,int) ; 

void dp_disable_link_phy(struct dc_link *link, enum signal_type signal)
{
	if (!link->wa_flags.dp_keep_receiver_powered)
		dp_receiver_power_ctrl(link, false);

	if (signal == SIGNAL_TYPE_EDP) {
		link->link_enc->funcs->disable_output(link->link_enc, signal);
		link->dc->hwss.edp_power_control(link, false);
	} else
		link->link_enc->funcs->disable_output(link->link_enc, signal);

	/* Clear current link setting.*/
	memset(&link->cur_link_settings, 0,
			sizeof(link->cur_link_settings));
}