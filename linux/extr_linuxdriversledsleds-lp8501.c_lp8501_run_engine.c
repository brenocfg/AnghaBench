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
 scalar_t__ LP8501_ENG1_IS_LOADING (int) ; 
 scalar_t__ LP8501_ENG2_IS_LOADING (int) ; 
 scalar_t__ LP8501_ENG3_IS_LOADING (int) ; 
 int LP8501_EXEC_ENG1_M ; 
 int LP8501_EXEC_ENG2_M ; 
 int LP8501_EXEC_ENG3_M ; 
 int /*<<< orphan*/  LP8501_EXEC_M ; 
 int LP8501_MODE_ENG1_M ; 
 int LP8501_MODE_ENG2_M ; 
 int LP8501_MODE_ENG3_M ; 
 int /*<<< orphan*/  LP8501_REG_ENABLE ; 
 int /*<<< orphan*/  LP8501_REG_OP_MODE ; 
 int LP8501_RUN_ENG1 ; 
 int LP8501_RUN_ENG2 ; 
 int LP8501_RUN_ENG3 ; 
 int lp55xx_read (struct lp55xx_chip*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  lp55xx_update_bits (struct lp55xx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lp55xx_write (struct lp55xx_chip*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lp8501_stop_engine (struct lp55xx_chip*) ; 
 int /*<<< orphan*/  lp8501_turn_off_channels (struct lp55xx_chip*) ; 
 int /*<<< orphan*/  lp8501_wait_opmode_done () ; 

__attribute__((used)) static void lp8501_run_engine(struct lp55xx_chip *chip, bool start)
{
	int ret;
	u8 mode;
	u8 exec;

	/* stop engine */
	if (!start) {
		lp8501_stop_engine(chip);
		lp8501_turn_off_channels(chip);
		return;
	}

	/*
	 * To run the engine,
	 * operation mode and enable register should updated at the same time
	 */

	ret = lp55xx_read(chip, LP8501_REG_OP_MODE, &mode);
	if (ret)
		return;

	ret = lp55xx_read(chip, LP8501_REG_ENABLE, &exec);
	if (ret)
		return;

	/* change operation mode to RUN only when each engine is loading */
	if (LP8501_ENG1_IS_LOADING(mode)) {
		mode = (mode & ~LP8501_MODE_ENG1_M) | LP8501_RUN_ENG1;
		exec = (exec & ~LP8501_EXEC_ENG1_M) | LP8501_RUN_ENG1;
	}

	if (LP8501_ENG2_IS_LOADING(mode)) {
		mode = (mode & ~LP8501_MODE_ENG2_M) | LP8501_RUN_ENG2;
		exec = (exec & ~LP8501_EXEC_ENG2_M) | LP8501_RUN_ENG2;
	}

	if (LP8501_ENG3_IS_LOADING(mode)) {
		mode = (mode & ~LP8501_MODE_ENG3_M) | LP8501_RUN_ENG3;
		exec = (exec & ~LP8501_EXEC_ENG3_M) | LP8501_RUN_ENG3;
	}

	lp55xx_write(chip, LP8501_REG_OP_MODE, mode);
	lp8501_wait_opmode_done();

	lp55xx_update_bits(chip, LP8501_REG_ENABLE, LP8501_EXEC_M, exec);
}