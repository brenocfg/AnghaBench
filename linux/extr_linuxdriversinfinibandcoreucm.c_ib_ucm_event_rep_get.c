#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ib_ucm_rep_event_resp {int /*<<< orphan*/  srq; int /*<<< orphan*/  rnr_retry_count; int /*<<< orphan*/  flow_control; int /*<<< orphan*/  failover_accepted; int /*<<< orphan*/  target_ack_delay; int /*<<< orphan*/  initiator_depth; int /*<<< orphan*/  responder_resources; int /*<<< orphan*/  starting_psn; int /*<<< orphan*/  remote_qpn; int /*<<< orphan*/  remote_qkey; int /*<<< orphan*/  remote_ca_guid; } ;
struct ib_cm_rep_event_param {int /*<<< orphan*/  srq; int /*<<< orphan*/  rnr_retry_count; int /*<<< orphan*/  flow_control; int /*<<< orphan*/  failover_accepted; int /*<<< orphan*/  target_ack_delay; int /*<<< orphan*/  initiator_depth; int /*<<< orphan*/  responder_resources; int /*<<< orphan*/  starting_psn; int /*<<< orphan*/  remote_qpn; int /*<<< orphan*/  remote_qkey; int /*<<< orphan*/  remote_ca_guid; } ;

/* Variables and functions */

__attribute__((used)) static void ib_ucm_event_rep_get(struct ib_ucm_rep_event_resp *urep,
				 const struct ib_cm_rep_event_param *krep)
{
	urep->remote_ca_guid      = krep->remote_ca_guid;
	urep->remote_qkey         = krep->remote_qkey;
	urep->remote_qpn          = krep->remote_qpn;
	urep->starting_psn        = krep->starting_psn;
	urep->responder_resources = krep->responder_resources;
	urep->initiator_depth     = krep->initiator_depth;
	urep->target_ack_delay    = krep->target_ack_delay;
	urep->failover_accepted   = krep->failover_accepted;
	urep->flow_control        = krep->flow_control;
	urep->rnr_retry_count     = krep->rnr_retry_count;
	urep->srq                 = krep->srq;
}