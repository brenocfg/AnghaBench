#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  size_t u32 ;
struct i40iw_update_sds_info {size_t cnt; int /*<<< orphan*/ * entry; int /*<<< orphan*/  hmc_fn_id; } ;
struct i40iw_sc_dev {TYPE_7__* cqp; } ;
struct TYPE_11__ {int /*<<< orphan*/  pa; } ;
struct TYPE_12__ {TYPE_4__ addr; } ;
struct TYPE_9__ {int /*<<< orphan*/  pa; } ;
struct TYPE_10__ {TYPE_2__ pd_page_addr; } ;
struct TYPE_13__ {TYPE_5__ bp; TYPE_3__ pd_table; } ;
struct i40iw_hmc_sd_entry {scalar_t__ entry_type; TYPE_6__ u; scalar_t__ valid; } ;
struct TYPE_8__ {struct i40iw_hmc_sd_entry* sd_entry; } ;
struct i40iw_hmc_info {TYPE_1__ sd_table; int /*<<< orphan*/  hmc_fn_id; } ;
typedef  int /*<<< orphan*/  sdinfo ;
typedef  enum i40iw_status_code { ____Placeholder_i40iw_status_code } i40iw_status_code ;
struct TYPE_14__ {int (* process_cqp_sds ) (struct i40iw_sc_dev*,struct i40iw_update_sds_info*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  I40IW_DEBUG_HMC ; 
 size_t I40IW_MAX_SD_ENTRIES ; 
 scalar_t__ I40IW_SD_TYPE_PAGED ; 
 int /*<<< orphan*/  i40iw_clr_sd_entry (size_t,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i40iw_debug (struct i40iw_sc_dev*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  i40iw_set_sd_entry (int /*<<< orphan*/ ,size_t,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct i40iw_update_sds_info*,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct i40iw_sc_dev*,struct i40iw_update_sds_info*) ; 
 int stub2 (struct i40iw_sc_dev*,struct i40iw_update_sds_info*) ; 

__attribute__((used)) static enum i40iw_status_code i40iw_hmc_sd_grp(struct i40iw_sc_dev *dev,
					       struct i40iw_hmc_info *hmc_info,
					       u32 sd_index,
					       u32 sd_cnt,
					       bool setsd)
{
	struct i40iw_hmc_sd_entry *sd_entry;
	struct i40iw_update_sds_info sdinfo;
	u64 pa;
	u32 i;
	enum i40iw_status_code ret_code = 0;

	memset(&sdinfo, 0, sizeof(sdinfo));
	sdinfo.hmc_fn_id = hmc_info->hmc_fn_id;
	for (i = sd_index; i < sd_index + sd_cnt; i++) {
		sd_entry = &hmc_info->sd_table.sd_entry[i];
		if (!sd_entry ||
		    (!sd_entry->valid && setsd) ||
		    (sd_entry->valid && !setsd))
			continue;
		if (setsd) {
			pa = (sd_entry->entry_type == I40IW_SD_TYPE_PAGED) ?
			    sd_entry->u.pd_table.pd_page_addr.pa :
			    sd_entry->u.bp.addr.pa;
			i40iw_set_sd_entry(pa, i, sd_entry->entry_type,
					   &sdinfo.entry[sdinfo.cnt]);
		} else {
			i40iw_clr_sd_entry(i, sd_entry->entry_type,
					   &sdinfo.entry[sdinfo.cnt]);
		}
		sdinfo.cnt++;
		if (sdinfo.cnt == I40IW_MAX_SD_ENTRIES) {
			ret_code = dev->cqp->process_cqp_sds(dev, &sdinfo);
			if (ret_code) {
				i40iw_debug(dev, I40IW_DEBUG_HMC,
					    "i40iw_hmc_sd_grp: sd_programming failed err=%d\n",
					    ret_code);
				return ret_code;
			}
			sdinfo.cnt = 0;
		}
	}
	if (sdinfo.cnt)
		ret_code = dev->cqp->process_cqp_sds(dev, &sdinfo);

	return ret_code;
}