#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct dc {int link_count; TYPE_7__** links; TYPE_2__* res_pool; } ;
typedef  enum signal_type { ____Placeholder_signal_type } signal_type ;
typedef  enum connector_id { ____Placeholder_connector_id } connector_id ;
struct TYPE_10__ {int /*<<< orphan*/  dp_keep_receiver_powered; } ;
struct TYPE_14__ {TYPE_5__* link_enc; TYPE_3__ wa_flags; int /*<<< orphan*/  link_id; } ;
struct TYPE_13__ {TYPE_1__* funcs; } ;
struct TYPE_12__ {TYPE_4__* funcs; } ;
struct TYPE_11__ {int /*<<< orphan*/  (* disable_output ) (TYPE_5__*,int) ;} ;
struct TYPE_9__ {int stream_enc_count; TYPE_6__** stream_enc; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* dp_blank ) (TYPE_6__*) ;} ;

/* Variables and functions */
 int CONNECTOR_ID_DISPLAY_PORT ; 
 int CONNECTOR_ID_EDP ; 
 int SIGNAL_TYPE_EDP ; 
 int SIGNAL_TYPE_NONE ; 
 int dal_graphics_object_id_get_connector_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dp_receiver_power_ctrl (TYPE_7__*,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_6__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_5__*,int) ; 

__attribute__((used)) static void power_down_encoders(struct dc *dc)
{
	int i;
	enum connector_id connector_id;
	enum signal_type signal = SIGNAL_TYPE_NONE;

	/* do not know BIOS back-front mapping, simply blank all. It will not
	 * hurt for non-DP
	 */
	for (i = 0; i < dc->res_pool->stream_enc_count; i++) {
		dc->res_pool->stream_enc[i]->funcs->dp_blank(
					dc->res_pool->stream_enc[i]);
	}

	for (i = 0; i < dc->link_count; i++) {
		connector_id = dal_graphics_object_id_get_connector_id(dc->links[i]->link_id);
		if ((connector_id == CONNECTOR_ID_DISPLAY_PORT) ||
			(connector_id == CONNECTOR_ID_EDP)) {

			if (!dc->links[i]->wa_flags.dp_keep_receiver_powered)
				dp_receiver_power_ctrl(dc->links[i], false);
			if (connector_id == CONNECTOR_ID_EDP)
				signal = SIGNAL_TYPE_EDP;
		}

		dc->links[i]->link_enc->funcs->disable_output(
				dc->links[i]->link_enc, signal);
	}
}