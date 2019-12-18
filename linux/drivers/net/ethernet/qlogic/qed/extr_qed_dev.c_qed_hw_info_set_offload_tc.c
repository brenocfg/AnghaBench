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
typedef  int /*<<< orphan*/  u8 ;
struct qed_hw_info {int offload_tc_set; int /*<<< orphan*/  offload_tc; } ;

/* Variables and functions */

void qed_hw_info_set_offload_tc(struct qed_hw_info *p_info, u8 tc)
{
	p_info->offload_tc = tc;
	p_info->offload_tc_set = true;
}