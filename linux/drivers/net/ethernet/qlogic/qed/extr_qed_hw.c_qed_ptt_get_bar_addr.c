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
typedef  scalar_t__ u32 ;
struct qed_ptt {int idx; } ;

/* Variables and functions */
 int PXP_EXTERNAL_BAR_PF_WINDOW_SINGLE_SIZE ; 
 scalar_t__ PXP_EXTERNAL_BAR_PF_WINDOW_START ; 

u32 qed_ptt_get_bar_addr(struct qed_ptt *p_ptt)
{
	return PXP_EXTERNAL_BAR_PF_WINDOW_START +
	       p_ptt->idx * PXP_EXTERNAL_BAR_PF_WINDOW_SINGLE_SIZE;
}