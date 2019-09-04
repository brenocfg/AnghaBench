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
struct lgdt3306a_state {int dummy; } ;
typedef  enum lgdt3306a_neverlock_status { ____Placeholder_lgdt3306a_neverlock_status } lgdt3306a_neverlock_status ;

/* Variables and functions */
 int LG3306_NL_FAIL ; 
 int LG3306_NL_LOCK ; 
 int /*<<< orphan*/  dbg_info (char*,int) ; 
 int lgdt3306a_check_neverlock_status (struct lgdt3306a_state*) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static enum lgdt3306a_neverlock_status
lgdt3306a_neverlock_poll(struct lgdt3306a_state *state)
{
	enum lgdt3306a_neverlock_status NLLockStatus = LG3306_NL_FAIL;
	int	i;

	for (i = 0; i < 5; i++) {
		msleep(30);

		NLLockStatus = lgdt3306a_check_neverlock_status(state);

		if (NLLockStatus == LG3306_NL_LOCK) {
			dbg_info("NL_LOCK(%d)\n", i);
			return NLLockStatus;
		}
	}
	dbg_info("NLLockStatus=%d\n", NLLockStatus);
	return NLLockStatus;
}