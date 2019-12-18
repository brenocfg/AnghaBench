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
struct lp55xx_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LP5521_REG_OP_MODE ; 
 int /*<<< orphan*/  lp5521_wait_opmode_done () ; 
 int /*<<< orphan*/  lp55xx_write (struct lp55xx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lp5521_stop_all_engines(struct lp55xx_chip *chip)
{
	lp55xx_write(chip, LP5521_REG_OP_MODE, 0);
	lp5521_wait_opmode_done();
}