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
typedef  int u64 ;
typedef  size_t u32 ;
struct i40iw_hmc_obj_info {int base; int cnt; int size; } ;
typedef  enum i40iw_status_code { ____Placeholder_i40iw_status_code } i40iw_status_code ;

/* Variables and functions */
 size_t I40IW_HMC_IW_APBVT_ENTRY ; 
 size_t I40IW_HMC_IW_CQ ; 
 size_t I40IW_HMC_IW_FSIAV ; 
 size_t I40IW_HMC_IW_FSIMC ; 
 size_t I40IW_HMC_IW_PBLE ; 
 size_t I40IW_HMC_IW_QP ; 
 size_t I40IW_HMC_IW_SRQ ; 
 int /*<<< orphan*/  I40IW_QUERY_FPM_MAX_CQS ; 
 int /*<<< orphan*/  I40IW_QUERY_FPM_MAX_QPS ; 
 scalar_t__ RS_64 (int,int /*<<< orphan*/ ) ; 
 int RS_64_1 (int,int) ; 
 int /*<<< orphan*/  get_64bit_val (int*,size_t,int*) ; 

__attribute__((used)) static enum i40iw_status_code i40iw_sc_parse_fpm_commit_buf(
				u64 *buf,
				struct i40iw_hmc_obj_info *info,
				u32 *sd)
{
	u64 temp;
	u64 size;
	u64 base = 0;
	u32 i, j;
	u32 k = 0;

	/* copy base values in obj_info */
	for (i = I40IW_HMC_IW_QP, j = 0; i <= I40IW_HMC_IW_PBLE; i++, j += 8) {
		if ((i == I40IW_HMC_IW_SRQ) ||
			(i == I40IW_HMC_IW_FSIMC) ||
			(i == I40IW_HMC_IW_FSIAV)) {
			info[i].base = 0;
			info[i].cnt = 0;
			continue;
		}
		get_64bit_val(buf, j, &temp);
		info[i].base = RS_64_1(temp, 32) * 512;
		if (info[i].base > base) {
			base = info[i].base;
			k = i;
		}
		if (i == I40IW_HMC_IW_APBVT_ENTRY) {
			info[i].cnt = 1;
			continue;
		}
		if (i == I40IW_HMC_IW_QP)
			info[i].cnt = (u32)RS_64(temp, I40IW_QUERY_FPM_MAX_QPS);
		else if (i == I40IW_HMC_IW_CQ)
			info[i].cnt = (u32)RS_64(temp, I40IW_QUERY_FPM_MAX_CQS);
		else
			info[i].cnt = (u32)(temp);
	}
	size = info[k].cnt * info[k].size + info[k].base;
	if (size & 0x1FFFFF)
		*sd = (u32)((size >> 21) + 1); /* add 1 for remainder */
	else
		*sd = (u32)(size >> 21);

	return 0;
}