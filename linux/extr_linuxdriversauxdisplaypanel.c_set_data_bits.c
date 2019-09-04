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

/* Variables and functions */
 int /*<<< orphan*/  LCD_PORT_D ; 
 int /*<<< orphan*/  lcd_get_bits (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pprt ; 
 int r_dtr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w_dtr (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int set_data_bits(void)
{
	int val;

	val = r_dtr(pprt);
	lcd_get_bits(LCD_PORT_D, &val);
	w_dtr(pprt, val);
	return val;
}