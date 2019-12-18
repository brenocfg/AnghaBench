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
typedef  enum lgdt3306a_lock_status { ____Placeholder_lgdt3306a_lock_status } lgdt3306a_lock_status ;

/* Variables and functions */
 int /*<<< orphan*/  LG3306_FEC_LOCK ; 
 int LG3306_LOCK ; 
 int LG3306_UNLOCK ; 
 int /*<<< orphan*/  dbg_info (char*,...) ; 
 int lgdt3306a_check_lock_status (struct lgdt3306a_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static enum lgdt3306a_lock_status
lgdt3306a_fec_lock_poll(struct lgdt3306a_state *state)
{
	enum lgdt3306a_lock_status FECLockStatus = LG3306_UNLOCK;
	int	i;

	for (i = 0; i < 2; i++)	{
		msleep(30);

		FECLockStatus = lgdt3306a_check_lock_status(state,
							    LG3306_FEC_LOCK);

		if (FECLockStatus == LG3306_LOCK) {
			dbg_info("locked(%d)\n", i);
			return FECLockStatus;
		}
	}
	dbg_info("not locked\n");
	return FECLockStatus;
}