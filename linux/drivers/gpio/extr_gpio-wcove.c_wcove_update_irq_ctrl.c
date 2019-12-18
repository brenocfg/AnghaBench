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
struct wcove_gpio {int /*<<< orphan*/  intcnt; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTLI_INTCNT_BE ; 
 int /*<<< orphan*/  CTRL_IN ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int to_reg (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wcove_update_irq_ctrl(struct wcove_gpio *wg, int gpio)
{
	int reg = to_reg(gpio, CTRL_IN);

	if (reg < 0)
		return;

	regmap_update_bits(wg->regmap, reg, CTLI_INTCNT_BE, wg->intcnt);
}