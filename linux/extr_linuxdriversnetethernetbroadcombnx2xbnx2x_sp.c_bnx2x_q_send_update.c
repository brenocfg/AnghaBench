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
typedef  size_t u8 ;
struct client_update_ramrod_data {int dummy; } ;
struct bnx2x_queue_update_params {size_t cid_index; } ;
struct TYPE_2__ {struct bnx2x_queue_update_params update; } ;
struct bnx2x_queue_state_params {TYPE_1__ params; struct bnx2x_queue_sp_obj* q_obj; } ;
struct bnx2x_queue_sp_obj {size_t max_cos; int /*<<< orphan*/ * cids; int /*<<< orphan*/  cl_id; int /*<<< orphan*/  rdata_mapping; scalar_t__ rdata; } ;
struct bnx2x {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*,int /*<<< orphan*/ ,size_t) ; 
 int EINVAL ; 
 int /*<<< orphan*/  ETH_CONNECTION_TYPE ; 
 int /*<<< orphan*/  RAMROD_CMD_ID_ETH_CLIENT_UPDATE ; 
 int /*<<< orphan*/  U64_HI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  U64_LO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_q_fill_update_data (struct bnx2x*,struct bnx2x_queue_sp_obj*,struct bnx2x_queue_update_params*,struct client_update_ramrod_data*) ; 
 int bnx2x_sp_post (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct client_update_ramrod_data*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int bnx2x_q_send_update(struct bnx2x *bp,
				      struct bnx2x_queue_state_params *params)
{
	struct bnx2x_queue_sp_obj *o = params->q_obj;
	struct client_update_ramrod_data *rdata =
		(struct client_update_ramrod_data *)o->rdata;
	dma_addr_t data_mapping = o->rdata_mapping;
	struct bnx2x_queue_update_params *update_params =
		&params->params.update;
	u8 cid_index = update_params->cid_index;

	if (cid_index >= o->max_cos) {
		BNX2X_ERR("queue[%d]: cid_index (%d) is out of range\n",
			  o->cl_id, cid_index);
		return -EINVAL;
	}

	/* Clear the ramrod data */
	memset(rdata, 0, sizeof(*rdata));

	/* Fill the ramrod data */
	bnx2x_q_fill_update_data(bp, o, update_params, rdata);

	/* No need for an explicit memory barrier here as long as we
	 * ensure the ordering of writing to the SPQ element
	 * and updating of the SPQ producer which involves a memory
	 * read. If the memory read is removed we will have to put a
	 * full memory barrier there (inside bnx2x_sp_post()).
	 */
	return bnx2x_sp_post(bp, RAMROD_CMD_ID_ETH_CLIENT_UPDATE,
			     o->cids[cid_index], U64_HI(data_mapping),
			     U64_LO(data_mapping), ETH_CONNECTION_TYPE);
}