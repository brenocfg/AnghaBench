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
struct bnx2x {scalar_t__ panic; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*,int) ; 
 int /*<<< orphan*/  BNX2X_MSG_SP ; 
 scalar_t__ CHIP_REV_IS_EMUL (struct bnx2x*) ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int) ; 
 int EBUSY ; 
 int EIO ; 
 int /*<<< orphan*/  bnx2x_panic () ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  test_bit (int,unsigned long*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static inline int bnx2x_state_wait(struct bnx2x *bp, int state,
				   unsigned long *pstate)
{
	/* can take a while if any port is running */
	int cnt = 5000;

	if (CHIP_REV_IS_EMUL(bp))
		cnt *= 20;

	DP(BNX2X_MSG_SP, "waiting for state to become %d\n", state);

	might_sleep();
	while (cnt--) {
		if (!test_bit(state, pstate)) {
#ifdef BNX2X_STOP_ON_ERROR
			DP(BNX2X_MSG_SP, "exit  (cnt %d)\n", 5000 - cnt);
#endif
			return 0;
		}

		usleep_range(1000, 2000);

		if (bp->panic)
			return -EIO;
	}

	/* timeout! */
	BNX2X_ERR("timeout waiting for state %d\n", state);
#ifdef BNX2X_STOP_ON_ERROR
	bnx2x_panic();
#endif

	return -EBUSY;
}