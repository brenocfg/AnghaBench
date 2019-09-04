#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  scalar_t__ u16 ;
struct stmpe {int /*<<< orphan*/ * regs; TYPE_1__* variant; } ;
struct TYPE_2__ {scalar_t__ id_val; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ STMPE811_ID ; 
 int STMPE811_SYS_CTRL_RESET ; 
 size_t STMPE_IDX_SYS_CTRL ; 
 int STMPE_SYS_CTRL_RESET ; 
 int __stmpe_reg_read (struct stmpe*,int /*<<< orphan*/ ) ; 
 int __stmpe_set_bits (struct stmpe*,int /*<<< orphan*/ ,int,int) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int stmpe_reset(struct stmpe *stmpe)
{
	u16 id_val = stmpe->variant->id_val;
	unsigned long timeout;
	int ret = 0;
	u8 reset_bit;

	if (id_val == STMPE811_ID)
		/* STMPE801 and STMPE610 use bit 1 of SYS_CTRL register */
		reset_bit = STMPE811_SYS_CTRL_RESET;
	else
		/* all other STMPE variant use bit 7 of SYS_CTRL register */
		reset_bit = STMPE_SYS_CTRL_RESET;

	ret = __stmpe_set_bits(stmpe, stmpe->regs[STMPE_IDX_SYS_CTRL],
			       reset_bit, reset_bit);
	if (ret < 0)
		return ret;

	msleep(10);

	timeout = jiffies + msecs_to_jiffies(100);
	while (time_before(jiffies, timeout)) {
		ret = __stmpe_reg_read(stmpe, stmpe->regs[STMPE_IDX_SYS_CTRL]);
		if (ret < 0)
			return ret;
		if (!(ret & reset_bit))
			return 0;
		usleep_range(100, 200);
	}
	return -EIO;
}