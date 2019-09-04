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
typedef  int /*<<< orphan*/  u8 ;
struct v4l2_subdev {int dummy; } ;
struct adv76xx_state {int /*<<< orphan*/ * regmap; TYPE_1__* info; } ;
struct TYPE_2__ {int page_mask; } ;

/* Variables and functions */
 unsigned int ADV76XX_PAGE_MAX ; 
 int BIT (unsigned int) ; 
 int EINVAL ; 
 int regmap_write (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 struct adv76xx_state* to_state (struct v4l2_subdev*) ; 

__attribute__((used)) static int adv76xx_write_reg(struct v4l2_subdev *sd, unsigned int reg, u8 val)
{
	struct adv76xx_state *state = to_state(sd);
	unsigned int page = reg >> 8;

	if (page >= ADV76XX_PAGE_MAX || !(BIT(page) & state->info->page_mask))
		return -EINVAL;

	reg &= 0xff;

	return regmap_write(state->regmap[page], reg, val);
}