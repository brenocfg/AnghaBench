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
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int BNX2X_NUM_ETH_QUEUES (struct bnx2x*) ; 

__attribute__((used)) static int bnx2x_num_stat_queues(struct bnx2x *bp)
{
	return BNX2X_NUM_ETH_QUEUES(bp);
}