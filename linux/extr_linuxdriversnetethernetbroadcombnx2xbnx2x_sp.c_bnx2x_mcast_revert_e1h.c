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
struct bnx2x_mcast_ramrod_params {int dummy; } ;
struct bnx2x {int dummy; } ;
typedef  enum bnx2x_mcast_cmd { ____Placeholder_bnx2x_mcast_cmd } bnx2x_mcast_cmd ;

/* Variables and functions */

__attribute__((used)) static void bnx2x_mcast_revert_e1h(struct bnx2x *bp,
				       struct bnx2x_mcast_ramrod_params *p,
				       int old_num_bins,
				       enum bnx2x_mcast_cmd cmd)
{
	/* Do nothing */
}