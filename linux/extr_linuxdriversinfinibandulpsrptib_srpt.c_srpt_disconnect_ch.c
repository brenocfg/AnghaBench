#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  cm_id; } ;
struct TYPE_3__ {int /*<<< orphan*/  cm_id; } ;
struct srpt_rdma_ch {TYPE_2__ ib_cm; TYPE_1__ rdma_cm; scalar_t__ using_rdma_cm; } ;

/* Variables and functions */
 int /*<<< orphan*/  CH_DISCONNECTING ; 
 int ENOTCONN ; 
 int ib_send_cm_drep (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ib_send_cm_dreq (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int rdma_disconnect (int /*<<< orphan*/ ) ; 
 scalar_t__ srpt_close_ch (struct srpt_rdma_ch*) ; 
 int /*<<< orphan*/  srpt_set_ch_state (struct srpt_rdma_ch*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int srpt_disconnect_ch(struct srpt_rdma_ch *ch)
{
	int ret;

	if (!srpt_set_ch_state(ch, CH_DISCONNECTING))
		return -ENOTCONN;

	if (ch->using_rdma_cm) {
		ret = rdma_disconnect(ch->rdma_cm.cm_id);
	} else {
		ret = ib_send_cm_dreq(ch->ib_cm.cm_id, NULL, 0);
		if (ret < 0)
			ret = ib_send_cm_drep(ch->ib_cm.cm_id, NULL, 0);
	}

	if (ret < 0 && srpt_close_ch(ch))
		ret = 0;

	return ret;
}