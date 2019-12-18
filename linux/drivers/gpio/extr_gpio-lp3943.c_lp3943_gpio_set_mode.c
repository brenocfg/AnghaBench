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
typedef  size_t u8 ;
struct lp3943_reg_cfg {size_t shift; int /*<<< orphan*/  mask; int /*<<< orphan*/  reg; } ;
struct lp3943_gpio {struct lp3943* lp3943; } ;
struct lp3943 {struct lp3943_reg_cfg* mux_cfg; } ;

/* Variables and functions */
 int lp3943_update_bits (struct lp3943*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int lp3943_gpio_set_mode(struct lp3943_gpio *lp3943_gpio, u8 offset,
				u8 val)
{
	struct lp3943 *lp3943 = lp3943_gpio->lp3943;
	const struct lp3943_reg_cfg *mux = lp3943->mux_cfg;

	return lp3943_update_bits(lp3943, mux[offset].reg, mux[offset].mask,
				  val << mux[offset].shift);
}