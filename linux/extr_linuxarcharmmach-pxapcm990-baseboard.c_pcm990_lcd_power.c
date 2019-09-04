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
struct fb_var_screeninfo {int dummy; } ;

/* Variables and functions */
 scalar_t__ PCM990_CTRL_LCDON ; 
 scalar_t__ PCM990_CTRL_LCDPWR ; 
 int /*<<< orphan*/  PCM990_CTRL_REG3 ; 
 int /*<<< orphan*/  pcm990_cpld_writeb (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pcm990_lcd_power(int on, struct fb_var_screeninfo *var)
{
	if (on) {
		/* enable LCD-Latches
		 * power on LCD
		 */
		pcm990_cpld_writeb(PCM990_CTRL_LCDPWR + PCM990_CTRL_LCDON,
				PCM990_CTRL_REG3);
	} else {
		/* disable LCD-Latches
		 * power off LCD
		 */
		pcm990_cpld_writeb(0, PCM990_CTRL_REG3);
	}
}