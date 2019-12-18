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
 int /*<<< orphan*/  BNX2X_MAX_QUEUES (struct bnx2x*) ; 
 scalar_t__ bnx2x_num_queues ; 
 int clamp (int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ is_kdump_kernel () ; 
 int netif_get_num_default_rss_queues () ; 

__attribute__((used)) static int bnx2x_calc_num_queues(struct bnx2x *bp)
{
	int nq = bnx2x_num_queues ? : netif_get_num_default_rss_queues();

	/* Reduce memory usage in kdump environment by using only one queue */
	if (is_kdump_kernel())
		nq = 1;

	nq = clamp(nq, 1, BNX2X_MAX_QUEUES(bp));
	return nq;
}