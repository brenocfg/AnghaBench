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
struct dcn10_mpc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  MPCC_BUSY ; 
 int /*<<< orphan*/  MPCC_IDLE ; 
 int /*<<< orphan*/ * MPCC_STATUS ; 
 int /*<<< orphan*/ * MPCC_TOP_SEL ; 
 int /*<<< orphan*/  REG_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int*) ; 
 int /*<<< orphan*/  REG_GET_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*,int /*<<< orphan*/ ,unsigned int*) ; 
 struct dcn10_mpc* TO_DCN10_MPC (struct mpc*) ; 

void mpc1_assert_mpcc_idle_before_connect(struct mpc *mpc, int mpcc_id)
{
	struct dcn10_mpc *mpc10 = TO_DCN10_MPC(mpc);
	unsigned int top_sel, mpc_busy, mpc_idle;

	REG_GET(MPCC_TOP_SEL[mpcc_id],
			MPCC_TOP_SEL, &top_sel);

	if (top_sel == 0xf) {
		REG_GET_2(MPCC_STATUS[mpcc_id],
				MPCC_BUSY, &mpc_busy,
				MPCC_IDLE, &mpc_idle);

		ASSERT(mpc_busy == 0);
		ASSERT(mpc_idle == 1);
	}
}