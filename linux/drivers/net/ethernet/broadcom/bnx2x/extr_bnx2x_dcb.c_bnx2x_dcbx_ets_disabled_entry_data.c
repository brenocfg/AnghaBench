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
typedef  int /*<<< orphan*/  u32 ;
struct cos_help_data {int num_of_cos; TYPE_1__* data; } ;
struct bnx2x {int dummy; } ;
struct TYPE_2__ {int cos_bw; int /*<<< orphan*/  pri_join_mask; int /*<<< orphan*/  pausable; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_DCBX_PFC_PRI_ONLY_PAUSE (struct bnx2x*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnx2x_dcbx_ets_disabled_entry_data(struct bnx2x *bp,
					       struct cos_help_data *cos_data,
					       u32 pri_join_mask)
{
	/* Only one priority than only one COS */
	cos_data->data[0].pausable =
		IS_DCBX_PFC_PRI_ONLY_PAUSE(bp, pri_join_mask);
	cos_data->data[0].pri_join_mask = pri_join_mask;
	cos_data->data[0].cos_bw = 100;
	cos_data->num_of_cos = 1;
}