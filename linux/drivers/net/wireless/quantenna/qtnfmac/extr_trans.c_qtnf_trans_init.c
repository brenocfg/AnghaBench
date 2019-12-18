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
struct TYPE_2__ {int waiting_for_resp; int /*<<< orphan*/  resp_lock; int /*<<< orphan*/ * resp_skb; scalar_t__ seq_num; int /*<<< orphan*/  cmd_resp_completion; } ;
struct qtnf_qlink_transport {int /*<<< orphan*/  event_queue_max_len; int /*<<< orphan*/  event_queue; TYPE_1__ curr_cmd; } ;
struct qtnf_bus {struct qtnf_qlink_transport trans; } ;

/* Variables and functions */
 int /*<<< orphan*/  QTNF_MAX_EVENT_QUEUE_LEN ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void qtnf_trans_init(struct qtnf_bus *bus)
{
	struct qtnf_qlink_transport *trans = &bus->trans;

	init_completion(&trans->curr_cmd.cmd_resp_completion);
	spin_lock_init(&trans->curr_cmd.resp_lock);

	spin_lock(&trans->curr_cmd.resp_lock);
	trans->curr_cmd.seq_num = 0;
	trans->curr_cmd.waiting_for_resp = false;
	trans->curr_cmd.resp_skb = NULL;
	spin_unlock(&trans->curr_cmd.resp_lock);

	/* Init event handling related fields */
	skb_queue_head_init(&trans->event_queue);
	trans->event_queue_max_len = QTNF_MAX_EVENT_QUEUE_LEN;
}