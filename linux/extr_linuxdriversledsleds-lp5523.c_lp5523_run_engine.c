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
typedef  int u8 ;
struct lp55xx_chip {int dummy; } ;

/* Variables and functions */
 scalar_t__ LP5523_ENG1_IS_LOADING (int) ; 
 scalar_t__ LP5523_ENG2_IS_LOADING (int) ; 
 scalar_t__ LP5523_ENG3_IS_LOADING (int) ; 
 int LP5523_EXEC_ENG1_M ; 
 int LP5523_EXEC_ENG2_M ; 
 int LP5523_EXEC_ENG3_M ; 
 int /*<<< orphan*/  LP5523_EXEC_M ; 
 int LP5523_MODE_ENG1_M ; 
 int LP5523_MODE_ENG2_M ; 
 int LP5523_MODE_ENG3_M ; 
 int /*<<< orphan*/  LP5523_REG_ENABLE ; 
 int /*<<< orphan*/  LP5523_REG_OP_MODE ; 
 int LP5523_RUN_ENG1 ; 
 int LP5523_RUN_ENG2 ; 
 int LP5523_RUN_ENG3 ; 
 int /*<<< orphan*/  lp5523_stop_engine (struct lp55xx_chip*) ; 
 int /*<<< orphan*/  lp5523_turn_off_channels (struct lp55xx_chip*) ; 
 int /*<<< orphan*/  lp5523_wait_opmode_done () ; 
 int lp55xx_read (struct lp55xx_chip*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  lp55xx_update_bits (struct lp55xx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lp55xx_write (struct lp55xx_chip*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void lp5523_run_engine(struct lp55xx_chip *chip, bool start)
{
	int ret;
	u8 mode;
	u8 exec;

	/* stop engine */
	if (!start) {
		lp5523_stop_engine(chip);
		lp5523_turn_off_channels(chip);
		return;
	}

	/*
	 * To run the engine,
	 * operation mode and enable register should updated at the same time
	 */

	ret = lp55xx_read(chip, LP5523_REG_OP_MODE, &mode);
	if (ret)
		return;

	ret = lp55xx_read(chip, LP5523_REG_ENABLE, &exec);
	if (ret)
		return;

	/* change operation mode to RUN only when each engine is loading */
	if (LP5523_ENG1_IS_LOADING(mode)) {
		mode = (mode & ~LP5523_MODE_ENG1_M) | LP5523_RUN_ENG1;
		exec = (exec & ~LP5523_EXEC_ENG1_M) | LP5523_RUN_ENG1;
	}

	if (LP5523_ENG2_IS_LOADING(mode)) {
		mode = (mode & ~LP5523_MODE_ENG2_M) | LP5523_RUN_ENG2;
		exec = (exec & ~LP5523_EXEC_ENG2_M) | LP5523_RUN_ENG2;
	}

	if (LP5523_ENG3_IS_LOADING(mode)) {
		mode = (mode & ~LP5523_MODE_ENG3_M) | LP5523_RUN_ENG3;
		exec = (exec & ~LP5523_EXEC_ENG3_M) | LP5523_RUN_ENG3;
	}

	lp55xx_write(chip, LP5523_REG_OP_MODE, mode);
	lp5523_wait_opmode_done();

	lp55xx_update_bits(chip, LP5523_REG_ENABLE, LP5523_EXEC_M, exec);
}