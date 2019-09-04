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
struct charlcd {int height; int hwidth; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCD_BIT_E ; 
 int /*<<< orphan*/  LCD_BIT_RS ; 
 int /*<<< orphan*/  LCD_BIT_RW ; 
 int /*<<< orphan*/  bits ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pprt ; 
 int /*<<< orphan*/  pprt_lock ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_ctrl_bits () ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  w_dtr (int /*<<< orphan*/ ,char) ; 

__attribute__((used)) static void lcd_clear_fast_p8(struct charlcd *charlcd)
{
	int pos;

	spin_lock_irq(&pprt_lock);
	for (pos = 0; pos < charlcd->height * charlcd->hwidth; pos++) {
		/* present the data to the data port */
		w_dtr(pprt, ' ');

		/* maintain the data during 20 us before the strobe */
		udelay(20);

		set_bit(LCD_BIT_E, bits);
		set_bit(LCD_BIT_RS, bits);
		clear_bit(LCD_BIT_RW, bits);
		set_ctrl_bits();

		/* maintain the strobe during 40 us */
		udelay(40);

		clear_bit(LCD_BIT_E, bits);
		set_ctrl_bits();

		/* the shortest data takes at least 45 us */
		udelay(45);
	}
	spin_unlock_irq(&pprt_lock);
}