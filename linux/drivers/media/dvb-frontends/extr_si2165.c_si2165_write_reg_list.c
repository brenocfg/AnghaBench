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
struct si2165_state {int dummy; } ;
struct si2165_reg_value_pair {int /*<<< orphan*/  val; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int si2165_writereg8 (struct si2165_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int si2165_write_reg_list(struct si2165_state *state,
				 const struct si2165_reg_value_pair *regs,
				 int count)
{
	int i;
	int ret;

	for (i = 0; i < count; i++) {
		ret = si2165_writereg8(state, regs[i].reg, regs[i].val);
		if (ret < 0)
			return ret;
	}
	return 0;
}