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
typedef  int u16 ;
struct tpa_update_ramrod_data {int dummy; } ;
struct bnx2x_queue_update_tpa_params {int dummy; } ;
struct TYPE_2__ {struct bnx2x_queue_update_tpa_params update_tpa; } ;
struct bnx2x_queue_state_params {TYPE_1__ params; struct bnx2x_queue_sp_obj* q_obj; } ;
struct bnx2x_queue_sp_obj {int func_id; int /*<<< orphan*/ * cids; int /*<<< orphan*/  rdata_mapping; scalar_t__ rdata; } ;
struct bnx2x {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 size_t BNX2X_PRIMARY_CID_INDEX ; 
 int ETH_CONNECTION_TYPE ; 
 int /*<<< orphan*/  RAMROD_CMD_ID_ETH_TPA_UPDATE ; 
 int SPE_HDR_FUNCTION_ID_SHIFT ; 
 int /*<<< orphan*/  U64_HI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  U64_LO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_q_fill_update_tpa_data (struct bnx2x*,struct bnx2x_queue_sp_obj*,struct bnx2x_queue_update_tpa_params*,struct tpa_update_ramrod_data*) ; 
 int bnx2x_sp_post (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct tpa_update_ramrod_data*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int bnx2x_q_send_update_tpa(struct bnx2x *bp,
					struct bnx2x_queue_state_params *params)
{
	struct bnx2x_queue_sp_obj *o = params->q_obj;
	struct tpa_update_ramrod_data *rdata =
		(struct tpa_update_ramrod_data *)o->rdata;
	dma_addr_t data_mapping = o->rdata_mapping;
	struct bnx2x_queue_update_tpa_params *update_tpa_params =
		&params->params.update_tpa;
	u16 type;

	/* Clear the ramrod data */
	memset(rdata, 0, sizeof(*rdata));

	/* Fill the ramrod data */
	bnx2x_q_fill_update_tpa_data(bp, o, update_tpa_params, rdata);

	/* Add the function id inside the type, so that sp post function
	 * doesn't automatically add the PF func-id, this is required
	 * for operations done by PFs on behalf of their VFs
	 */
	type = ETH_CONNECTION_TYPE |
		((o->func_id) << SPE_HDR_FUNCTION_ID_SHIFT);

	/* No need for an explicit memory barrier here as long as we
	 * ensure the ordering of writing to the SPQ element
	 * and updating of the SPQ producer which involves a memory
	 * read. If the memory read is removed we will have to put a
	 * full memory barrier there (inside bnx2x_sp_post()).
	 */
	return bnx2x_sp_post(bp, RAMROD_CMD_ID_ETH_TPA_UPDATE,
			     o->cids[BNX2X_PRIMARY_CID_INDEX],
			     U64_HI(data_mapping),
			     U64_LO(data_mapping), type);
}