#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct i40e_hw {int dummy; } ;
struct i40e_hmc_pd_table {TYPE_3__* pd_entry; } ;
struct i40e_hmc_lan_delete_obj_info {scalar_t__ start_idx; size_t rsrc_type; scalar_t__ count; TYPE_6__* hmc_info; } ;
typedef  scalar_t__ i40e_status ;
struct TYPE_15__ {size_t sd_cnt; TYPE_4__* sd_entry; } ;
struct TYPE_16__ {scalar_t__ signature; TYPE_5__ sd_table; TYPE_1__* hmc_obj; } ;
struct TYPE_12__ {struct i40e_hmc_pd_table pd_table; } ;
struct TYPE_14__ {int entry_type; int /*<<< orphan*/  valid; TYPE_2__ u; } ;
struct TYPE_13__ {scalar_t__ valid; } ;
struct TYPE_11__ {scalar_t__ cnt; } ;

/* Variables and functions */
 scalar_t__ I40E_ERR_BAD_PTR ; 
 scalar_t__ I40E_ERR_INVALID_HMC_OBJ_COUNT ; 
 scalar_t__ I40E_ERR_INVALID_HMC_OBJ_INDEX ; 
 scalar_t__ I40E_ERR_INVALID_SD_INDEX ; 
 int /*<<< orphan*/  I40E_FIND_PD_INDEX_LIMIT (TYPE_6__*,size_t,scalar_t__,scalar_t__,size_t*,size_t*) ; 
 int /*<<< orphan*/  I40E_FIND_SD_INDEX_LIMIT (TYPE_6__*,size_t,scalar_t__,scalar_t__,size_t*,size_t*) ; 
 scalar_t__ I40E_HMC_INFO_SIGNATURE ; 
 size_t I40E_HMC_PD_CNT_IN_SD ; 
#define  I40E_SD_TYPE_DIRECT 129 
#define  I40E_SD_TYPE_PAGED 128 
 int /*<<< orphan*/  hw_dbg (struct i40e_hw*,char*,...) ; 
 scalar_t__ i40e_remove_pd_bp (struct i40e_hw*,TYPE_6__*,size_t) ; 
 scalar_t__ i40e_remove_pd_page (struct i40e_hw*,TYPE_6__*,size_t) ; 
 scalar_t__ i40e_remove_sd_bp (struct i40e_hw*,TYPE_6__*,size_t) ; 

__attribute__((used)) static i40e_status i40e_delete_lan_hmc_object(struct i40e_hw *hw,
				struct i40e_hmc_lan_delete_obj_info *info)
{
	i40e_status ret_code = 0;
	struct i40e_hmc_pd_table *pd_table;
	u32 pd_idx, pd_lmt, rel_pd_idx;
	u32 sd_idx, sd_lmt;
	u32 i, j;

	if (NULL == info) {
		ret_code = I40E_ERR_BAD_PTR;
		hw_dbg(hw, "i40e_delete_hmc_object: bad info ptr\n");
		goto exit;
	}
	if (NULL == info->hmc_info) {
		ret_code = I40E_ERR_BAD_PTR;
		hw_dbg(hw, "i40e_delete_hmc_object: bad info->hmc_info ptr\n");
		goto exit;
	}
	if (I40E_HMC_INFO_SIGNATURE != info->hmc_info->signature) {
		ret_code = I40E_ERR_BAD_PTR;
		hw_dbg(hw, "i40e_delete_hmc_object: bad hmc_info->signature\n");
		goto exit;
	}

	if (NULL == info->hmc_info->sd_table.sd_entry) {
		ret_code = I40E_ERR_BAD_PTR;
		hw_dbg(hw, "i40e_delete_hmc_object: bad sd_entry\n");
		goto exit;
	}

	if (NULL == info->hmc_info->hmc_obj) {
		ret_code = I40E_ERR_BAD_PTR;
		hw_dbg(hw, "i40e_delete_hmc_object: bad hmc_info->hmc_obj\n");
		goto exit;
	}
	if (info->start_idx >= info->hmc_info->hmc_obj[info->rsrc_type].cnt) {
		ret_code = I40E_ERR_INVALID_HMC_OBJ_INDEX;
		hw_dbg(hw, "i40e_delete_hmc_object: returns error %d\n",
			  ret_code);
		goto exit;
	}

	if ((info->start_idx + info->count) >
	    info->hmc_info->hmc_obj[info->rsrc_type].cnt) {
		ret_code = I40E_ERR_INVALID_HMC_OBJ_COUNT;
		hw_dbg(hw, "i40e_delete_hmc_object: returns error %d\n",
			  ret_code);
		goto exit;
	}

	I40E_FIND_PD_INDEX_LIMIT(info->hmc_info, info->rsrc_type,
				 info->start_idx, info->count, &pd_idx,
				 &pd_lmt);

	for (j = pd_idx; j < pd_lmt; j++) {
		sd_idx = j / I40E_HMC_PD_CNT_IN_SD;

		if (I40E_SD_TYPE_PAGED !=
		    info->hmc_info->sd_table.sd_entry[sd_idx].entry_type)
			continue;

		rel_pd_idx = j % I40E_HMC_PD_CNT_IN_SD;

		pd_table =
			&info->hmc_info->sd_table.sd_entry[sd_idx].u.pd_table;
		if (pd_table->pd_entry[rel_pd_idx].valid) {
			ret_code = i40e_remove_pd_bp(hw, info->hmc_info, j);
			if (ret_code)
				goto exit;
		}
	}

	/* find sd index and limit */
	I40E_FIND_SD_INDEX_LIMIT(info->hmc_info, info->rsrc_type,
				 info->start_idx, info->count,
				 &sd_idx, &sd_lmt);
	if (sd_idx >= info->hmc_info->sd_table.sd_cnt ||
	    sd_lmt > info->hmc_info->sd_table.sd_cnt) {
		ret_code = I40E_ERR_INVALID_SD_INDEX;
		goto exit;
	}

	for (i = sd_idx; i < sd_lmt; i++) {
		if (!info->hmc_info->sd_table.sd_entry[i].valid)
			continue;
		switch (info->hmc_info->sd_table.sd_entry[i].entry_type) {
		case I40E_SD_TYPE_DIRECT:
			ret_code = i40e_remove_sd_bp(hw, info->hmc_info, i);
			if (ret_code)
				goto exit;
			break;
		case I40E_SD_TYPE_PAGED:
			ret_code = i40e_remove_pd_page(hw, info->hmc_info, i);
			if (ret_code)
				goto exit;
			break;
		default:
			break;
		}
	}
exit:
	return ret_code;
}