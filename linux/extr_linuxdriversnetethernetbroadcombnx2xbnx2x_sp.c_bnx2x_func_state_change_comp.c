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
struct bnx2x_func_sp_obj {unsigned long pending; int /*<<< orphan*/  next_state; int /*<<< orphan*/  state; } ;
struct bnx2x {int dummy; } ;
typedef  enum bnx2x_func_cmd { ____Placeholder_bnx2x_func_cmd } bnx2x_func_cmd ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BNX2X_F_STATE_MAX ; 
 int /*<<< orphan*/  BNX2X_MSG_SP ; 
 int /*<<< orphan*/  BP_FUNC (struct bnx2x*) ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  clear_bit (int,unsigned long*) ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 
 int /*<<< orphan*/  test_and_clear_bit (int,unsigned long*) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static inline int bnx2x_func_state_change_comp(struct bnx2x *bp,
					       struct bnx2x_func_sp_obj *o,
					       enum bnx2x_func_cmd cmd)
{
	unsigned long cur_pending = o->pending;

	if (!test_and_clear_bit(cmd, &cur_pending)) {
		BNX2X_ERR("Bad MC reply %d for func %d in state %d pending 0x%lx, next_state %d\n",
			  cmd, BP_FUNC(bp), o->state,
			  cur_pending, o->next_state);
		return -EINVAL;
	}

	DP(BNX2X_MSG_SP,
	   "Completing command %d for func %d, setting state to %d\n",
	   cmd, BP_FUNC(bp), o->next_state);

	o->state = o->next_state;
	o->next_state = BNX2X_F_STATE_MAX;

	/* It's important that o->state and o->next_state are
	 * updated before o->pending.
	 */
	wmb();

	clear_bit(cmd, &o->pending);
	smp_mb__after_atomic();

	return 0;
}