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
struct lgdt3305_state {int dummy; } ;
struct lgdt3305_reg {int /*<<< orphan*/  val; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 scalar_t__ lg_fail (int) ; 
 int /*<<< orphan*/  lg_reg (char*,int) ; 
 int lgdt3305_write_reg (struct lgdt3305_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lgdt3305_write_regs(struct lgdt3305_state *state,
			       struct lgdt3305_reg *regs, int len)
{
	int i, ret;

	lg_reg("writing %d registers...\n", len);

	for (i = 0; i < len - 1; i++) {
		ret = lgdt3305_write_reg(state, regs[i].reg, regs[i].val);
		if (lg_fail(ret))
			return ret;
	}
	return 0;
}