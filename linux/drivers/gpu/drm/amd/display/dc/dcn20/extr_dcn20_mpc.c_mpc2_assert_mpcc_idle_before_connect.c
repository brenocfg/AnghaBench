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
struct dcn20_mpc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  MPCC_BUSY ; 
 int /*<<< orphan*/  MPCC_DISABLED ; 
 int /*<<< orphan*/  MPCC_IDLE ; 
 int /*<<< orphan*/ * MPCC_STATUS ; 
 int /*<<< orphan*/ * MPCC_TOP_SEL ; 
 int /*<<< orphan*/  REG_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int*) ; 
 int /*<<< orphan*/  REG_GET_3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*,int /*<<< orphan*/ ,unsigned int*,int /*<<< orphan*/ ,unsigned int*) ; 
 struct dcn20_mpc* TO_DCN20_MPC (struct mpc*) ; 

void mpc2_assert_mpcc_idle_before_connect(struct mpc *mpc, int mpcc_id)
{
	struct dcn20_mpc *mpc20 = TO_DCN20_MPC(mpc);
	unsigned int top_sel, mpc_busy, mpc_idle, mpc_disabled;

	REG_GET(MPCC_TOP_SEL[mpcc_id],
			MPCC_TOP_SEL, &top_sel);

	REG_GET_3(MPCC_STATUS[mpcc_id],
			MPCC_BUSY, &mpc_busy,
			MPCC_IDLE, &mpc_idle,
			MPCC_DISABLED, &mpc_disabled);

	if (top_sel == 0xf) {
		ASSERT(!mpc_busy);
		ASSERT(mpc_idle);
		ASSERT(mpc_disabled);
	} else {
		ASSERT(!mpc_disabled);
		ASSERT(!mpc_idle);
	}
}