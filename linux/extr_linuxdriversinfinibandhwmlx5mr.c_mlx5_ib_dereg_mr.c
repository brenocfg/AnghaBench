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
struct ib_mr {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  dereg_mr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_mdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_mmr (struct ib_mr*) ; 

int mlx5_ib_dereg_mr(struct ib_mr *ibmr)
{
	dereg_mr(to_mdev(ibmr->device), to_mmr(ibmr));
	return 0;
}