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
typedef  int u8 ;
struct lgdt3306a_state {int dummy; } ;
typedef  enum lgdt3306a_neverlock_status { ____Placeholder_lgdt3306a_neverlock_status } lgdt3306a_neverlock_status ;

/* Variables and functions */
 int /*<<< orphan*/  dbg_info (char*,int) ; 
 int lgdt3306a_read_reg (struct lgdt3306a_state*,int,int*) ; 

__attribute__((used)) static enum lgdt3306a_neverlock_status
lgdt3306a_check_neverlock_status(struct lgdt3306a_state *state)
{
	u8 val = 0;
	int ret;
	enum lgdt3306a_neverlock_status lockStatus;

	ret = lgdt3306a_read_reg(state, 0x0080, &val);
	if (ret)
		return ret;
	lockStatus = (enum lgdt3306a_neverlock_status)(val & 0x03);

	dbg_info("NeverLock=%d", lockStatus);

	return lockStatus;
}