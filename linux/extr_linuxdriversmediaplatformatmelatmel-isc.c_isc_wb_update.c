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
typedef  scalar_t__ u32 ;
struct isc_ctrls {void* b_gain; void* r_gain; scalar_t__* hist_count; } ;

/* Variables and functions */
 size_t ISC_HIS_CFG_MODE_B ; 
 size_t ISC_HIS_CFG_MODE_GB ; 
 size_t ISC_HIS_CFG_MODE_R ; 
 void* div_u64 (int,scalar_t__) ; 

__attribute__((used)) static void isc_wb_update(struct isc_ctrls *ctrls)
{
	u32 *hist_count = &ctrls->hist_count[0];
	u64 g_count = (u64)hist_count[ISC_HIS_CFG_MODE_GB] << 9;
	u32 hist_r = hist_count[ISC_HIS_CFG_MODE_R];
	u32 hist_b = hist_count[ISC_HIS_CFG_MODE_B];

	if (hist_r)
		ctrls->r_gain = div_u64(g_count, hist_r);

	if (hist_b)
		ctrls->b_gain = div_u64(g_count, hist_b);
}