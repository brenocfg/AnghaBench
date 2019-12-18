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
typedef  scalar_t__ u64 ;
typedef  size_t u32 ;
struct i40iw_hmc_obj_info {size_t max_cnt; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  LS_64_1 (int,size_t) ; 
 scalar_t__ RS_64_1 (scalar_t__,int) ; 
 int /*<<< orphan*/  get_64bit_val (scalar_t__*,size_t,scalar_t__*) ; 

__attribute__((used)) static u64 i40iw_sc_decode_fpm_query(u64 *buf,
					    u32 buf_idx,
					    struct i40iw_hmc_obj_info *obj_info,
					    u32 rsrc_idx)
{
	u64 temp;
	u32 size;

	get_64bit_val(buf, buf_idx, &temp);
	obj_info[rsrc_idx].max_cnt = (u32)temp;
	size = (u32)RS_64_1(temp, 32);
	obj_info[rsrc_idx].size = LS_64_1(1, size);

	return temp;
}