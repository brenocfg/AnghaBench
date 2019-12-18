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
typedef  int /*<<< orphan*/  u8 ;
struct lp55xx_chip {int engine_idx; } ;
typedef  enum lp55xx_engine_index { ____Placeholder_lp55xx_engine_index } lp55xx_engine_index ;

/* Variables and functions */
#define  LP5521_MODE_B_M 133 
#define  LP5521_MODE_G_M 132 
#define  LP5521_MODE_R_M 131 
 int /*<<< orphan*/  LP5521_REG_OP_MODE ; 
#define  LP55XX_ENGINE_1 130 
#define  LP55XX_ENGINE_2 129 
#define  LP55XX_ENGINE_3 128 
 int /*<<< orphan*/  lp5521_wait_opmode_done () ; 
 int /*<<< orphan*/  lp55xx_update_bits (struct lp55xx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lp5521_stop_engine(struct lp55xx_chip *chip)
{
	enum lp55xx_engine_index idx = chip->engine_idx;
	static const u8 mask[] = {
		[LP55XX_ENGINE_1] = LP5521_MODE_R_M,
		[LP55XX_ENGINE_2] = LP5521_MODE_G_M,
		[LP55XX_ENGINE_3] = LP5521_MODE_B_M,
	};

	lp55xx_update_bits(chip, LP5521_REG_OP_MODE, mask[idx], 0);

	lp5521_wait_opmode_done();
}