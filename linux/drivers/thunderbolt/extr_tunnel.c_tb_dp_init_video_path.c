#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct tb_path {int priority; int weight; int nfc_credits; void* ingress_shared_buffer; void* ingress_fc_enable; void* egress_shared_buffer; void* egress_fc_enable; TYPE_3__* hops; } ;
struct TYPE_6__ {TYPE_2__* in_port; } ;
struct TYPE_4__ {int nfc_credits; } ;
struct TYPE_5__ {TYPE_1__ config; } ;

/* Variables and functions */
 void* TB_PATH_NONE ; 
 int TB_PORT_MAX_CREDITS_MASK ; 
 int TB_PORT_MAX_CREDITS_SHIFT ; 
 int TB_PORT_NFC_CREDITS_MASK ; 
 int min (int,unsigned int) ; 

__attribute__((used)) static void tb_dp_init_video_path(struct tb_path *path, bool discover)
{
	u32 nfc_credits = path->hops[0].in_port->config.nfc_credits;

	path->egress_fc_enable = TB_PATH_NONE;
	path->egress_shared_buffer = TB_PATH_NONE;
	path->ingress_fc_enable = TB_PATH_NONE;
	path->ingress_shared_buffer = TB_PATH_NONE;
	path->priority = 1;
	path->weight = 1;

	if (discover) {
		path->nfc_credits = nfc_credits & TB_PORT_NFC_CREDITS_MASK;
	} else {
		u32 max_credits;

		max_credits = (nfc_credits & TB_PORT_MAX_CREDITS_MASK) >>
			TB_PORT_MAX_CREDITS_SHIFT;
		/* Leave some credits for AUX path */
		path->nfc_credits = min(max_credits - 2, 12U);
	}
}