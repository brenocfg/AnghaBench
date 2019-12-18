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
struct bnx2x_queue_state_params {struct bnx2x_queue_sp_obj* q_obj; } ;
struct bnx2x_queue_sp_obj {int /*<<< orphan*/ * cids; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 size_t BNX2X_PRIMARY_CID_INDEX ; 
 int /*<<< orphan*/  ETH_CONNECTION_TYPE ; 
 int /*<<< orphan*/  RAMROD_CMD_ID_ETH_EMPTY ; 
 int bnx2x_sp_post (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int bnx2x_q_send_empty(struct bnx2x *bp,
				     struct bnx2x_queue_state_params *params)
{
	struct bnx2x_queue_sp_obj *o = params->q_obj;

	return bnx2x_sp_post(bp, RAMROD_CMD_ID_ETH_EMPTY,
			     o->cids[BNX2X_PRIMARY_CID_INDEX], 0, 0,
			     ETH_CONNECTION_TYPE);
}