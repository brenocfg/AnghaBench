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
 scalar_t__ LP5521_B_IS_LOADING (int) ; 
 int LP5521_CMD_DIRECT ; 
 int LP5521_EXEC_B_M ; 
 int LP5521_EXEC_G_M ; 
 int /*<<< orphan*/  LP5521_EXEC_M ; 
 int LP5521_EXEC_R_M ; 
 scalar_t__ LP5521_G_IS_LOADING (int) ; 
 int LP5521_MODE_B_M ; 
 int LP5521_MODE_G_M ; 
 int LP5521_MODE_R_M ; 
 int /*<<< orphan*/  LP5521_REG_ENABLE ; 
 int /*<<< orphan*/  LP5521_REG_OP_MODE ; 
 int LP5521_RUN_B ; 
 int LP5521_RUN_G ; 
 int LP5521_RUN_R ; 
 scalar_t__ LP5521_R_IS_LOADING (int) ; 
 int /*<<< orphan*/  lp5521_stop_engine (struct lp55xx_chip*) ; 
 int /*<<< orphan*/  lp5521_wait_enable_done () ; 
 int /*<<< orphan*/  lp5521_wait_opmode_done () ; 
 int lp55xx_read (struct lp55xx_chip*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  lp55xx_update_bits (struct lp55xx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lp55xx_write (struct lp55xx_chip*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void lp5521_run_engine(struct lp55xx_chip *chip, bool start)
{
	int ret;
	u8 mode;
	u8 exec;

	/* stop engine */
	if (!start) {
		lp5521_stop_engine(chip);
		lp55xx_write(chip, LP5521_REG_OP_MODE, LP5521_CMD_DIRECT);
		lp5521_wait_opmode_done();
		return;
	}

	/*
	 * To run the engine,
	 * operation mode and enable register should updated at the same time
	 */

	ret = lp55xx_read(chip, LP5521_REG_OP_MODE, &mode);
	if (ret)
		return;

	ret = lp55xx_read(chip, LP5521_REG_ENABLE, &exec);
	if (ret)
		return;

	/* change operation mode to RUN only when each engine is loading */
	if (LP5521_R_IS_LOADING(mode)) {
		mode = (mode & ~LP5521_MODE_R_M) | LP5521_RUN_R;
		exec = (exec & ~LP5521_EXEC_R_M) | LP5521_RUN_R;
	}

	if (LP5521_G_IS_LOADING(mode)) {
		mode = (mode & ~LP5521_MODE_G_M) | LP5521_RUN_G;
		exec = (exec & ~LP5521_EXEC_G_M) | LP5521_RUN_G;
	}

	if (LP5521_B_IS_LOADING(mode)) {
		mode = (mode & ~LP5521_MODE_B_M) | LP5521_RUN_B;
		exec = (exec & ~LP5521_EXEC_B_M) | LP5521_RUN_B;
	}

	lp55xx_write(chip, LP5521_REG_OP_MODE, mode);
	lp5521_wait_opmode_done();

	lp55xx_update_bits(chip, LP5521_REG_ENABLE, LP5521_EXEC_M, exec);
	lp5521_wait_enable_done();
}