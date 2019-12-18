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
struct client_init_ramrod_data {int dummy; } ;
struct bnx2x_queue_state_params {struct bnx2x_queue_sp_obj* q_obj; } ;
struct bnx2x_queue_sp_obj {int /*<<< orphan*/ * cids; int /*<<< orphan*/  rdata_mapping; scalar_t__ rdata; } ;
struct bnx2x {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 size_t BNX2X_PRIMARY_CID_INDEX ; 
 int /*<<< orphan*/  ETH_CONNECTION_TYPE ; 
 int RAMROD_CMD_ID_ETH_CLIENT_SETUP ; 
 int /*<<< orphan*/  U64_HI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  U64_LO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_q_fill_setup_data_cmn (struct bnx2x*,struct bnx2x_queue_state_params*,struct client_init_ramrod_data*) ; 
 int bnx2x_sp_post (struct bnx2x*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct client_init_ramrod_data*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int bnx2x_q_send_setup_e1x(struct bnx2x *bp,
					struct bnx2x_queue_state_params *params)
{
	struct bnx2x_queue_sp_obj *o = params->q_obj;
	struct client_init_ramrod_data *rdata =
		(struct client_init_ramrod_data *)o->rdata;
	dma_addr_t data_mapping = o->rdata_mapping;
	int ramrod = RAMROD_CMD_ID_ETH_CLIENT_SETUP;

	/* Clear the ramrod data */
	memset(rdata, 0, sizeof(*rdata));

	/* Fill the ramrod data */
	bnx2x_q_fill_setup_data_cmn(bp, params, rdata);

	/* No need for an explicit memory barrier here as long as we
	 * ensure the ordering of writing to the SPQ element
	 * and updating of the SPQ producer which involves a memory
	 * read. If the memory read is removed we will have to put a
	 * full memory barrier there (inside bnx2x_sp_post()).
	 */
	return bnx2x_sp_post(bp, ramrod, o->cids[BNX2X_PRIMARY_CID_INDEX],
			     U64_HI(data_mapping),
			     U64_LO(data_mapping), ETH_CONNECTION_TYPE);
}