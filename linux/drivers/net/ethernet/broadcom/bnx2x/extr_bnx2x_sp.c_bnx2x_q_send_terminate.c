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
typedef  size_t u8 ;
struct TYPE_3__ {size_t cid_index; } ;
struct TYPE_4__ {TYPE_1__ terminate; } ;
struct bnx2x_queue_state_params {TYPE_2__ params; struct bnx2x_queue_sp_obj* q_obj; } ;
struct bnx2x_queue_sp_obj {size_t max_cos; int /*<<< orphan*/ * cids; int /*<<< orphan*/  cl_id; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*,int /*<<< orphan*/ ,size_t) ; 
 int EINVAL ; 
 int /*<<< orphan*/  ETH_CONNECTION_TYPE ; 
 int /*<<< orphan*/  RAMROD_CMD_ID_ETH_TERMINATE ; 
 int bnx2x_sp_post (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int bnx2x_q_send_terminate(struct bnx2x *bp,
					struct bnx2x_queue_state_params *params)
{
	struct bnx2x_queue_sp_obj *o = params->q_obj;
	u8 cid_index = params->params.terminate.cid_index;

	if (cid_index >= o->max_cos) {
		BNX2X_ERR("queue[%d]: cid_index (%d) is out of range\n",
			  o->cl_id, cid_index);
		return -EINVAL;
	}

	return bnx2x_sp_post(bp, RAMROD_CMD_ID_ETH_TERMINATE,
			     o->cids[cid_index], 0, 0, ETH_CONNECTION_TYPE);
}