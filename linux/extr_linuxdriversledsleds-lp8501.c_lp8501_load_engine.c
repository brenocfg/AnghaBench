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
#define  LP55XX_ENGINE_1 139 
#define  LP55XX_ENGINE_2 138 
#define  LP55XX_ENGINE_3 137 
#define  LP8501_LOAD_ENG1 136 
#define  LP8501_LOAD_ENG2 135 
#define  LP8501_LOAD_ENG3 134 
#define  LP8501_MODE_ENG1_M 133 
#define  LP8501_MODE_ENG2_M 132 
#define  LP8501_MODE_ENG3_M 131 
#define  LP8501_PAGE_ENG1 130 
#define  LP8501_PAGE_ENG2 129 
#define  LP8501_PAGE_ENG3 128 
 int /*<<< orphan*/  LP8501_REG_OP_MODE ; 
 int /*<<< orphan*/  LP8501_REG_PROG_PAGE_SEL ; 
 int /*<<< orphan*/  lp55xx_update_bits (struct lp55xx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  lp55xx_write (struct lp55xx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  lp8501_wait_opmode_done () ; 

__attribute__((used)) static void lp8501_load_engine(struct lp55xx_chip *chip)
{
	enum lp55xx_engine_index idx = chip->engine_idx;
	static const u8 mask[] = {
		[LP55XX_ENGINE_1] = LP8501_MODE_ENG1_M,
		[LP55XX_ENGINE_2] = LP8501_MODE_ENG2_M,
		[LP55XX_ENGINE_3] = LP8501_MODE_ENG3_M,
	};

	static const u8 val[] = {
		[LP55XX_ENGINE_1] = LP8501_LOAD_ENG1,
		[LP55XX_ENGINE_2] = LP8501_LOAD_ENG2,
		[LP55XX_ENGINE_3] = LP8501_LOAD_ENG3,
	};

	static const u8 page_sel[] = {
		[LP55XX_ENGINE_1] = LP8501_PAGE_ENG1,
		[LP55XX_ENGINE_2] = LP8501_PAGE_ENG2,
		[LP55XX_ENGINE_3] = LP8501_PAGE_ENG3,
	};

	lp55xx_update_bits(chip, LP8501_REG_OP_MODE, mask[idx], val[idx]);

	lp8501_wait_opmode_done();

	lp55xx_write(chip, LP8501_REG_PROG_PAGE_SEL, page_sel[idx]);
}