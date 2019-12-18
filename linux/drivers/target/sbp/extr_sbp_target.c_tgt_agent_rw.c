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
struct TYPE_4__ {scalar_t__ offset; } ;
struct sbp_target_agent {TYPE_2__ handler; TYPE_1__* login; } ;
struct sbp_session {int generation; int node_id; int /*<<< orphan*/  lock; } ;
struct fw_request {int dummy; } ;
struct fw_card {int dummy; } ;
struct TYPE_3__ {struct sbp_session* sess; } ;

/* Variables and functions */
 int RCODE_ADDRESS_ERROR ; 
 int RCODE_TYPE_ERROR ; 
 int /*<<< orphan*/  fw_send_response (struct fw_card*,struct fw_request*,int) ; 
 int /*<<< orphan*/  pr_notice (char*,...) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int tgt_agent_rw_agent_reset (struct fw_card*,int,void*,struct sbp_target_agent*) ; 
 int tgt_agent_rw_agent_state (struct fw_card*,int,void*,struct sbp_target_agent*) ; 
 int tgt_agent_rw_doorbell (struct fw_card*,int,void*,struct sbp_target_agent*) ; 
 int tgt_agent_rw_orb_pointer (struct fw_card*,int,void*,struct sbp_target_agent*) ; 
 int tgt_agent_rw_unsolicited_status_enable (struct fw_card*,int,void*,struct sbp_target_agent*) ; 

__attribute__((used)) static void tgt_agent_rw(struct fw_card *card, struct fw_request *request,
		int tcode, int destination, int source, int generation,
		unsigned long long offset, void *data, size_t length,
		void *callback_data)
{
	struct sbp_target_agent *agent = callback_data;
	struct sbp_session *sess = agent->login->sess;
	int sess_gen, sess_node, rcode;

	spin_lock_bh(&sess->lock);
	sess_gen = sess->generation;
	sess_node = sess->node_id;
	spin_unlock_bh(&sess->lock);

	if (generation != sess_gen) {
		pr_notice("ignoring request with wrong generation\n");
		rcode = RCODE_TYPE_ERROR;
		goto out;
	}

	if (source != sess_node) {
		pr_notice("ignoring request from foreign node (%x != %x)\n",
				source, sess_node);
		rcode = RCODE_TYPE_ERROR;
		goto out;
	}

	/* turn offset into the offset from the start of the block */
	offset -= agent->handler.offset;

	if (offset == 0x00 && length == 4) {
		/* AGENT_STATE */
		rcode = tgt_agent_rw_agent_state(card, tcode, data, agent);
	} else if (offset == 0x04 && length == 4) {
		/* AGENT_RESET */
		rcode = tgt_agent_rw_agent_reset(card, tcode, data, agent);
	} else if (offset == 0x08 && length == 8) {
		/* ORB_POINTER */
		rcode = tgt_agent_rw_orb_pointer(card, tcode, data, agent);
	} else if (offset == 0x10 && length == 4) {
		/* DOORBELL */
		rcode = tgt_agent_rw_doorbell(card, tcode, data, agent);
	} else if (offset == 0x14 && length == 4) {
		/* UNSOLICITED_STATUS_ENABLE */
		rcode = tgt_agent_rw_unsolicited_status_enable(card, tcode,
				data, agent);
	} else {
		rcode = RCODE_ADDRESS_ERROR;
	}

out:
	fw_send_response(card, request, rcode);
}