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
struct mpc {int dummy; } ;
struct dcn10_mpc {int mpcc_in_use_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  MPCC_IDLE ; 
 int /*<<< orphan*/ * MPCC_STATUS ; 
 int /*<<< orphan*/  REG_WAIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 struct dcn10_mpc* TO_DCN10_MPC (struct mpc*) ; 

void mpc1_assert_idle_mpcc(struct mpc *mpc, int id)
{
	struct dcn10_mpc *mpc10 = TO_DCN10_MPC(mpc);

	ASSERT(!(mpc10->mpcc_in_use_mask & 1 << id));
	REG_WAIT(MPCC_STATUS[id],
			MPCC_IDLE, 1,
			1, 100000);
}