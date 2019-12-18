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
struct lp55xx_led {size_t chan_nr; int /*<<< orphan*/  chip; int /*<<< orphan*/  led_current; } ;

/* Variables and functions */
#define  LP5562_REG_B_CURRENT 131 
#define  LP5562_REG_G_CURRENT 130 
#define  LP5562_REG_R_CURRENT 129 
#define  LP5562_REG_W_CURRENT 128 
 int /*<<< orphan*/  lp55xx_write (int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lp5562_set_led_current(struct lp55xx_led *led, u8 led_current)
{
	static const u8 addr[] = {
		LP5562_REG_R_CURRENT,
		LP5562_REG_G_CURRENT,
		LP5562_REG_B_CURRENT,
		LP5562_REG_W_CURRENT,
	};

	led->led_current = led_current;
	lp55xx_write(led->chip, addr[led->chan_nr], led_current);
}