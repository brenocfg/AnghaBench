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
typedef  scalar_t__ u8 ;
struct TYPE_4__ {int /*<<< orphan*/  val; } ;
struct function_start_data {int sd_accept_mf_clss_fail_match_ethtype; int /*<<< orphan*/  c2s_pri_default; TYPE_2__ c2s_pri_trans_table; scalar_t__ c2s_pri_tt_valid; int /*<<< orphan*/  no_added_tags; void* sd_vlan_eth_type; int /*<<< orphan*/  sd_vlan_force_pri_val; int /*<<< orphan*/  sd_vlan_force_pri_flg; void* sd_accept_mf_clss_fail_ethtype; int /*<<< orphan*/  sd_accept_mf_clss_fail; int /*<<< orphan*/  inner_rss; int /*<<< orphan*/  inner_clss_vxlan; int /*<<< orphan*/  inner_clss_l2geneve; int /*<<< orphan*/  inner_clss_l2gre; void* geneve_dst_port; void* vxlan_dst_port; int /*<<< orphan*/  dmae_cmd_id; int /*<<< orphan*/  network_cos_mode; int /*<<< orphan*/  path_id; void* sd_vlan_tag; scalar_t__ function_mode; } ;
struct bnx2x_func_start_params {int sd_vlan_tag; int vxlan_dst_port; int geneve_dst_port; int class_fail_ethtype; int sd_vlan_eth_type; int /*<<< orphan*/  c2s_pri_default; int /*<<< orphan*/  c2s_pri; scalar_t__ c2s_pri_valid; int /*<<< orphan*/  no_added_tags; int /*<<< orphan*/  sd_vlan_force_pri_val; int /*<<< orphan*/  sd_vlan_force_pri; int /*<<< orphan*/  class_fail; int /*<<< orphan*/  inner_rss; int /*<<< orphan*/  inner_clss_vxlan; int /*<<< orphan*/  inner_clss_l2geneve; int /*<<< orphan*/  inner_clss_l2gre; int /*<<< orphan*/  network_cos_mode; scalar_t__ mf_mode; } ;
struct TYPE_3__ {struct bnx2x_func_start_params start; } ;
struct bnx2x_func_state_params {TYPE_1__ params; struct bnx2x_func_sp_obj* f_obj; } ;
struct bnx2x_func_sp_obj {int /*<<< orphan*/  rdata_mapping; scalar_t__ rdata; } ;
struct bnx2x {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_FW_DMAE_C ; 
 int /*<<< orphan*/  BP_PATH (struct bnx2x*) ; 
 int /*<<< orphan*/  MAX_VLAN_PRIORITIES ; 
 int /*<<< orphan*/  NONE_CONNECTION_TYPE ; 
 int /*<<< orphan*/  RAMROD_CMD_ID_COMMON_FUNCTION_START ; 
 int /*<<< orphan*/  U64_HI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  U64_LO (int /*<<< orphan*/ ) ; 
 int bnx2x_sp_post (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct function_start_data*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int bnx2x_func_send_start(struct bnx2x *bp,
					struct bnx2x_func_state_params *params)
{
	struct bnx2x_func_sp_obj *o = params->f_obj;
	struct function_start_data *rdata =
		(struct function_start_data *)o->rdata;
	dma_addr_t data_mapping = o->rdata_mapping;
	struct bnx2x_func_start_params *start_params = &params->params.start;

	memset(rdata, 0, sizeof(*rdata));

	/* Fill the ramrod data with provided parameters */
	rdata->function_mode	= (u8)start_params->mf_mode;
	rdata->sd_vlan_tag	= cpu_to_le16(start_params->sd_vlan_tag);
	rdata->path_id		= BP_PATH(bp);
	rdata->network_cos_mode	= start_params->network_cos_mode;
	rdata->dmae_cmd_id	= BNX2X_FW_DMAE_C;

	rdata->vxlan_dst_port	= cpu_to_le16(start_params->vxlan_dst_port);
	rdata->geneve_dst_port	= cpu_to_le16(start_params->geneve_dst_port);
	rdata->inner_clss_l2gre	= start_params->inner_clss_l2gre;
	rdata->inner_clss_l2geneve = start_params->inner_clss_l2geneve;
	rdata->inner_clss_vxlan	= start_params->inner_clss_vxlan;
	rdata->inner_rss	= start_params->inner_rss;

	rdata->sd_accept_mf_clss_fail = start_params->class_fail;
	if (start_params->class_fail_ethtype) {
		rdata->sd_accept_mf_clss_fail_match_ethtype = 1;
		rdata->sd_accept_mf_clss_fail_ethtype =
			cpu_to_le16(start_params->class_fail_ethtype);
	}

	rdata->sd_vlan_force_pri_flg = start_params->sd_vlan_force_pri;
	rdata->sd_vlan_force_pri_val = start_params->sd_vlan_force_pri_val;
	if (start_params->sd_vlan_eth_type)
		rdata->sd_vlan_eth_type =
			cpu_to_le16(start_params->sd_vlan_eth_type);
	else
		rdata->sd_vlan_eth_type =
			cpu_to_le16(0x8100);

	rdata->no_added_tags = start_params->no_added_tags;

	rdata->c2s_pri_tt_valid = start_params->c2s_pri_valid;
	if (rdata->c2s_pri_tt_valid) {
		memcpy(rdata->c2s_pri_trans_table.val,
		       start_params->c2s_pri,
		       MAX_VLAN_PRIORITIES);
		rdata->c2s_pri_default = start_params->c2s_pri_default;
	}
	/* No need for an explicit memory barrier here as long we would
	 * need to ensure the ordering of writing to the SPQ element
	 * and updating of the SPQ producer which involves a memory
	 * read and we will have to put a full memory barrier there
	 * (inside bnx2x_sp_post()).
	 */

	return bnx2x_sp_post(bp, RAMROD_CMD_ID_COMMON_FUNCTION_START, 0,
			     U64_HI(data_mapping),
			     U64_LO(data_mapping), NONE_CONNECTION_TYPE);
}