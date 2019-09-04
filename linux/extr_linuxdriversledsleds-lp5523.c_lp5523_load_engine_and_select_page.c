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
#define  LP5523_PAGE_ENG1 133 
#define  LP5523_PAGE_ENG2 132 
#define  LP5523_PAGE_ENG3 131 
 int /*<<< orphan*/  LP5523_REG_PROG_PAGE_SEL ; 
#define  LP55XX_ENGINE_1 130 
#define  LP55XX_ENGINE_2 129 
#define  LP55XX_ENGINE_3 128 
 int /*<<< orphan*/  lp5523_load_engine (struct lp55xx_chip*) ; 
 int /*<<< orphan*/  lp55xx_write (struct lp55xx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 

__attribute__((used)) static void lp5523_load_engine_and_select_page(struct lp55xx_chip *chip)
{
	enum lp55xx_engine_index idx = chip->engine_idx;
	static const u8 page_sel[] = {
		[LP55XX_ENGINE_1] = LP5523_PAGE_ENG1,
		[LP55XX_ENGINE_2] = LP5523_PAGE_ENG2,
		[LP55XX_ENGINE_3] = LP5523_PAGE_ENG3,
	};

	lp5523_load_engine(chip);

	lp55xx_write(chip, LP5523_REG_PROG_PAGE_SEL, page_sel[idx]);
}