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
struct st_keyscan {int debounce_us; int n_cols; int n_rows; scalar_t__ base; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int KEYSCAN_CONFIG_ENABLE ; 
 scalar_t__ KEYSCAN_CONFIG_OFF ; 
 scalar_t__ KEYSCAN_DEBOUNCE_TIME_OFF ; 
 scalar_t__ KEYSCAN_MATRIX_DIM_OFF ; 
 int KEYSCAN_MATRIX_DIM_X_SHIFT ; 
 int KEYSCAN_MATRIX_DIM_Y_SHIFT ; 
 int clk_enable (int /*<<< orphan*/ ) ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int keyscan_start(struct st_keyscan *keypad)
{
	int error;

	error = clk_enable(keypad->clk);
	if (error)
		return error;

	writel(keypad->debounce_us * (clk_get_rate(keypad->clk) / 1000000),
	       keypad->base + KEYSCAN_DEBOUNCE_TIME_OFF);

	writel(((keypad->n_cols - 1) << KEYSCAN_MATRIX_DIM_X_SHIFT) |
	       ((keypad->n_rows - 1) << KEYSCAN_MATRIX_DIM_Y_SHIFT),
	       keypad->base + KEYSCAN_MATRIX_DIM_OFF);

	writel(KEYSCAN_CONFIG_ENABLE, keypad->base + KEYSCAN_CONFIG_OFF);

	return 0;
}