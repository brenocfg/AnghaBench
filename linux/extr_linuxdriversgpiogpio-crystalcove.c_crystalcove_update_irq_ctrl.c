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
struct crystalcove_gpio {int /*<<< orphan*/  intcnt_value; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTLI_INTCNT_BE ; 
 int /*<<< orphan*/  CTRL_IN ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int to_reg (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void crystalcove_update_irq_ctrl(struct crystalcove_gpio *cg, int gpio)
{
	int reg = to_reg(gpio, CTRL_IN);

	regmap_update_bits(cg->regmap, reg, CTLI_INTCNT_BE, cg->intcnt_value);
}