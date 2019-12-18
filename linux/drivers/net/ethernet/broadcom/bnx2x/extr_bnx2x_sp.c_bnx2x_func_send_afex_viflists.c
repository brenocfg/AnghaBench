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
typedef  int /*<<< orphan*/  u64 ;
struct bnx2x_func_afex_viflists_params {int /*<<< orphan*/  afex_vif_list_command; int /*<<< orphan*/  func_to_clear; int /*<<< orphan*/  func_bit_map; int /*<<< orphan*/  vif_list_index; } ;
struct TYPE_2__ {struct bnx2x_func_afex_viflists_params afex_viflists; } ;
struct bnx2x_func_state_params {TYPE_1__ params; struct bnx2x_func_sp_obj* f_obj; } ;
struct bnx2x_func_sp_obj {scalar_t__ afex_rdata; } ;
struct bnx2x {int dummy; } ;
struct afex_vif_list_ramrod_data {int /*<<< orphan*/  func_to_clear; int /*<<< orphan*/  func_bit_map; int /*<<< orphan*/  vif_list_index; int /*<<< orphan*/  afex_vif_list_command; int /*<<< orphan*/  echo; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_MSG_SP ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NONE_CONNECTION_TYPE ; 
 int /*<<< orphan*/  RAMROD_CMD_ID_COMMON_AFEX_VIF_LISTS ; 
 int /*<<< orphan*/  U64_HI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  U64_LO (int /*<<< orphan*/ ) ; 
 int bnx2x_sp_post (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct afex_vif_list_ramrod_data*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static
inline int bnx2x_func_send_afex_viflists(struct bnx2x *bp,
					 struct bnx2x_func_state_params *params)
{
	struct bnx2x_func_sp_obj *o = params->f_obj;
	struct afex_vif_list_ramrod_data *rdata =
		(struct afex_vif_list_ramrod_data *)o->afex_rdata;
	struct bnx2x_func_afex_viflists_params *afex_vif_params =
		&params->params.afex_viflists;
	u64 *p_rdata = (u64 *)rdata;

	memset(rdata, 0, sizeof(*rdata));

	/* Fill the ramrod data with provided parameters */
	rdata->vif_list_index = cpu_to_le16(afex_vif_params->vif_list_index);
	rdata->func_bit_map          = afex_vif_params->func_bit_map;
	rdata->afex_vif_list_command = afex_vif_params->afex_vif_list_command;
	rdata->func_to_clear         = afex_vif_params->func_to_clear;

	/* send in echo type of sub command */
	rdata->echo = afex_vif_params->afex_vif_list_command;

	/*  No need for an explicit memory barrier here as long we would
	 *  need to ensure the ordering of writing to the SPQ element
	 *  and updating of the SPQ producer which involves a memory
	 *  read and we will have to put a full memory barrier there
	 *  (inside bnx2x_sp_post()).
	 */

	DP(BNX2X_MSG_SP, "afex: ramrod lists, cmd 0x%x index 0x%x func_bit_map 0x%x func_to_clr 0x%x\n",
	   rdata->afex_vif_list_command, rdata->vif_list_index,
	   rdata->func_bit_map, rdata->func_to_clear);

	/* this ramrod sends data directly and not through DMA mapping */
	return bnx2x_sp_post(bp, RAMROD_CMD_ID_COMMON_AFEX_VIF_LISTS, 0,
			     U64_HI(*p_rdata), U64_LO(*p_rdata),
			     NONE_CONNECTION_TYPE);
}