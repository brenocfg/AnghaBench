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
 int IDP_CPLD_LCD ; 
 int /*<<< orphan*/  idp_vlcd (int) ; 

__attribute__((used)) static void idp_lcd_power(int on, struct fb_var_screeninfo *var)
{
	if (on) {
		IDP_CPLD_LCD |= (1<<0);
	} else {
		IDP_CPLD_LCD &= ~(1<<0);
	}

	/* call idp_vlcd for now as core driver does not support
	 * both power and vlcd hooks.  Note, this is not technically
	 * the correct sequence, but seems to work.  Disclaimer:
	 * this may eventually damage the display.
	 */

	idp_vlcd(on);
}