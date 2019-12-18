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
typedef  scalar_t__ u64 ;
struct sbp_tport {struct sbp_tpg* tpg; } ;
struct sbp_tpg {int dummy; } ;
struct TYPE_6__ {void* status; } ;
struct TYPE_4__ {int /*<<< orphan*/  misc; } ;
struct sbp_management_request {TYPE_3__ status; int /*<<< orphan*/  speed; int /*<<< orphan*/  card; int /*<<< orphan*/  node_addr; int /*<<< orphan*/  generation; TYPE_1__ orb; } ;
struct sbp_management_agent {struct sbp_tport* tport; } ;
struct sbp_login_descriptor {TYPE_2__* sess; } ;
struct TYPE_5__ {scalar_t__ guid; int /*<<< orphan*/  lock; int /*<<< orphan*/  speed; scalar_t__ card; int /*<<< orphan*/  node_id; int /*<<< orphan*/  generation; } ;

/* Variables and functions */
 int RCODE_COMPLETE ; 
 int /*<<< orphan*/  RECONNECT_ORB_LOGIN_ID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SBP_STATUS_ACCESS_DENIED ; 
 int /*<<< orphan*/  SBP_STATUS_OK ; 
 int /*<<< orphan*/  SBP_STATUS_UNSPECIFIED_ERROR ; 
 int STATUS_BLOCK_RESP (int /*<<< orphan*/ ) ; 
 int STATUS_BLOCK_SBP_STATUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_RESP_REQUEST_COMPLETE ; 
 int /*<<< orphan*/  STATUS_RESP_TRANSPORT_FAILURE ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 void* cpu_to_be32 (int) ; 
 scalar_t__ fw_card_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fw_card_put (scalar_t__) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_notice (char*,scalar_t__) ; 
 int /*<<< orphan*/  pr_warn (char*,int) ; 
 int read_peer_guid (scalar_t__*,struct sbp_management_request*) ; 
 struct sbp_login_descriptor* sbp_login_find_by_id (struct sbp_tpg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sbp_management_request_reconnect(
	struct sbp_management_agent *agent, struct sbp_management_request *req,
	int *status_data_size)
{
	struct sbp_tport *tport = agent->tport;
	struct sbp_tpg *tpg = tport->tpg;
	int ret;
	u64 guid;
	struct sbp_login_descriptor *login;

	ret = read_peer_guid(&guid, req);
	if (ret != RCODE_COMPLETE) {
		pr_warn("failed to read peer GUID: %d\n", ret);

		req->status.status = cpu_to_be32(
			STATUS_BLOCK_RESP(STATUS_RESP_TRANSPORT_FAILURE) |
			STATUS_BLOCK_SBP_STATUS(SBP_STATUS_UNSPECIFIED_ERROR));
		return;
	}

	pr_notice("mgt_agent RECONNECT from %016llx\n", guid);

	login = sbp_login_find_by_id(tpg,
		RECONNECT_ORB_LOGIN_ID(be32_to_cpu(req->orb.misc)));

	if (!login) {
		pr_err("mgt_agent RECONNECT unknown login ID\n");

		req->status.status = cpu_to_be32(
			STATUS_BLOCK_RESP(STATUS_RESP_REQUEST_COMPLETE) |
			STATUS_BLOCK_SBP_STATUS(SBP_STATUS_ACCESS_DENIED));
		return;
	}

	if (login->sess->guid != guid) {
		pr_err("mgt_agent RECONNECT login GUID doesn't match\n");

		req->status.status = cpu_to_be32(
			STATUS_BLOCK_RESP(STATUS_RESP_REQUEST_COMPLETE) |
			STATUS_BLOCK_SBP_STATUS(SBP_STATUS_ACCESS_DENIED));
		return;
	}

	spin_lock_bh(&login->sess->lock);
	if (login->sess->card)
		fw_card_put(login->sess->card);

	/* update the node details */
	login->sess->generation = req->generation;
	login->sess->node_id = req->node_addr;
	login->sess->card = fw_card_get(req->card);
	login->sess->speed = req->speed;
	spin_unlock_bh(&login->sess->lock);

	req->status.status = cpu_to_be32(
		STATUS_BLOCK_RESP(STATUS_RESP_REQUEST_COMPLETE) |
		STATUS_BLOCK_SBP_STATUS(SBP_STATUS_OK));
}