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
 int /*<<< orphan*/  bnx2x_stats_comp (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_stats_pmf_update (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_stats_start (struct bnx2x*) ; 

__attribute__((used)) static void bnx2x_stats_pmf_start(struct bnx2x *bp)
{
	bnx2x_stats_comp(bp);
	bnx2x_stats_pmf_update(bp);
	bnx2x_stats_start(bp);
}