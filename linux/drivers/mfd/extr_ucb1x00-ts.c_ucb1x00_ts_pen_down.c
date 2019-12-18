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
struct ucb1x00_ts {int /*<<< orphan*/  ucb; } ;

/* Variables and functions */
 int /*<<< orphan*/  UCB_TS_CR ; 
 unsigned int UCB_TS_CR_TSMX_LOW ; 
 unsigned int UCB_TS_CR_TSPX_LOW ; 
 scalar_t__ machine_is_collie () ; 
 unsigned int ucb1x00_reg_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int ucb1x00_ts_pen_down(struct ucb1x00_ts *ts)
{
	unsigned int val = ucb1x00_reg_read(ts->ucb, UCB_TS_CR);

	if (machine_is_collie())
		return (!(val & (UCB_TS_CR_TSPX_LOW)));
	else
		return (val & (UCB_TS_CR_TSPX_LOW | UCB_TS_CR_TSMX_LOW));
}