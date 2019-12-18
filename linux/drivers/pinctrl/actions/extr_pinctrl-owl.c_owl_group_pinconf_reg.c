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
typedef  int /*<<< orphan*/  u32 ;
struct owl_pingroup {int /*<<< orphan*/  sr_width; int /*<<< orphan*/  sr_shift; int /*<<< orphan*/  sr_reg; int /*<<< orphan*/  drv_width; int /*<<< orphan*/  drv_shift; int /*<<< orphan*/  drv_reg; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTSUPP ; 
#define  PIN_CONFIG_DRIVE_STRENGTH 129 
#define  PIN_CONFIG_SLEW_RATE 128 

__attribute__((used)) static int owl_group_pinconf_reg(const struct owl_pingroup *g,
				unsigned int param,
				u32 *reg,
				u32 *bit,
				u32 *width)
{
	switch (param) {
	case PIN_CONFIG_DRIVE_STRENGTH:
		if (g->drv_reg < 0)
			return -EINVAL;
		*reg = g->drv_reg;
		*bit = g->drv_shift;
		*width = g->drv_width;
		break;
	case PIN_CONFIG_SLEW_RATE:
		if (g->sr_reg < 0)
			return -EINVAL;
		*reg = g->sr_reg;
		*bit = g->sr_shift;
		*width = g->sr_width;
		break;
	default:
		return -ENOTSUPP;
	}

	return 0;
}