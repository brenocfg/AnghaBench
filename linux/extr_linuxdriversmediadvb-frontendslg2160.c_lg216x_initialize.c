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
struct lg216x_state {TYPE_1__* cfg; } ;
struct lg216x_reg {int reg; int val; } ;
struct TYPE_2__ {int lg_chip; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct lg216x_reg*) ; 
 int EINVAL ; 
#define  LG2160 129 
#define  LG2161 128 
 int lg216x_soft_reset (struct lg216x_state*) ; 
 int lg216x_write_regs (struct lg216x_state*,struct lg216x_reg*,int /*<<< orphan*/ ) ; 
 scalar_t__ lg_fail (int) ; 

__attribute__((used)) static int lg216x_initialize(struct lg216x_state *state)
{
	int ret;

	static struct lg216x_reg lg2160_init[] = {
#if 0
		{ .reg = 0x0015, .val = 0xe6 },
#else
		{ .reg = 0x0015, .val = 0xf7 },
		{ .reg = 0x001b, .val = 0x52 },
		{ .reg = 0x0208, .val = 0x00 },
		{ .reg = 0x0209, .val = 0x82 },
		{ .reg = 0x0210, .val = 0xf9 },
		{ .reg = 0x020a, .val = 0x00 },
		{ .reg = 0x020b, .val = 0x82 },
		{ .reg = 0x020d, .val = 0x28 },
		{ .reg = 0x020f, .val = 0x14 },
#endif
	};

	static struct lg216x_reg lg2161_init[] = {
		{ .reg = 0x0000, .val = 0x41 },
		{ .reg = 0x0001, .val = 0xfb },
		{ .reg = 0x0216, .val = 0x00 },
		{ .reg = 0x0219, .val = 0x00 },
		{ .reg = 0x021b, .val = 0x55 },
		{ .reg = 0x0606, .val = 0x0a },
	};

	switch (state->cfg->lg_chip) {
	case LG2160:
		ret = lg216x_write_regs(state,
					lg2160_init, ARRAY_SIZE(lg2160_init));
		break;
	case LG2161:
		ret = lg216x_write_regs(state,
					lg2161_init, ARRAY_SIZE(lg2161_init));
		break;
	default:
		ret = -EINVAL;
		break;
	}
	if (lg_fail(ret))
		goto fail;

	ret = lg216x_soft_reset(state);
	lg_fail(ret);
fail:
	return ret;
}