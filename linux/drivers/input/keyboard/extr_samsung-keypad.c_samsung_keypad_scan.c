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
struct samsung_keypad {unsigned int cols; scalar_t__ type; int rows; scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ KEYPAD_TYPE_S5PV210 ; 
 unsigned int S5PV210_KEYIFCOLEN_MASK ; 
 scalar_t__ SAMSUNG_KEYIFCOL ; 
 unsigned int SAMSUNG_KEYIFCOL_MASK ; 
 scalar_t__ SAMSUNG_KEYIFROW ; 
 int /*<<< orphan*/  mdelay (int) ; 
 unsigned int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static void samsung_keypad_scan(struct samsung_keypad *keypad,
				unsigned int *row_state)
{
	unsigned int col;
	unsigned int val;

	for (col = 0; col < keypad->cols; col++) {
		if (keypad->type == KEYPAD_TYPE_S5PV210) {
			val = S5PV210_KEYIFCOLEN_MASK;
			val &= ~(1 << col) << 8;
		} else {
			val = SAMSUNG_KEYIFCOL_MASK;
			val &= ~(1 << col);
		}

		writel(val, keypad->base + SAMSUNG_KEYIFCOL);
		mdelay(1);

		val = readl(keypad->base + SAMSUNG_KEYIFROW);
		row_state[col] = ~val & ((1 << keypad->rows) - 1);
	}

	/* KEYIFCOL reg clear */
	writel(0, keypad->base + SAMSUNG_KEYIFCOL);
}