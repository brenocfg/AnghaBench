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
typedef  size_t u32 ;
struct TYPE_2__ {size_t* init_val; int* b_valid; } ;
struct qed_hwfn {TYPE_1__ rt_data; } ;

/* Variables and functions */

void qed_init_store_rt_reg(struct qed_hwfn *p_hwfn, u32 rt_offset, u32 val)
{
	p_hwfn->rt_data.init_val[rt_offset] = val;
	p_hwfn->rt_data.b_valid[rt_offset] = true;
}