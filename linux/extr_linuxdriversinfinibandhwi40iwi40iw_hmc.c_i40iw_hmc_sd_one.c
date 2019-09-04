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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct i40iw_update_sds_info {int cnt; int /*<<< orphan*/  entry; int /*<<< orphan*/  hmc_fn_id; } ;
struct i40iw_sc_dev {TYPE_1__* cqp; } ;
typedef  enum i40iw_status_code { ____Placeholder_i40iw_status_code } i40iw_status_code ;
typedef  enum i40iw_sd_entry_type { ____Placeholder_i40iw_sd_entry_type } i40iw_sd_entry_type ;
struct TYPE_2__ {int (* process_cqp_sds ) (struct i40iw_sc_dev*,struct i40iw_update_sds_info*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  i40iw_clr_sd_entry (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40iw_set_sd_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int stub1 (struct i40iw_sc_dev*,struct i40iw_update_sds_info*) ; 

enum i40iw_status_code i40iw_hmc_sd_one(struct i40iw_sc_dev *dev,
					u8 hmc_fn_id,
					u64 pa, u32 sd_idx,
					enum i40iw_sd_entry_type type,
					bool setsd)
{
	struct i40iw_update_sds_info sdinfo;

	sdinfo.cnt = 1;
	sdinfo.hmc_fn_id = hmc_fn_id;
	if (setsd)
		i40iw_set_sd_entry(pa, sd_idx, type, sdinfo.entry);
	else
		i40iw_clr_sd_entry(sd_idx, type, sdinfo.entry);

	return dev->cqp->process_cqp_sds(dev, &sdinfo);
}