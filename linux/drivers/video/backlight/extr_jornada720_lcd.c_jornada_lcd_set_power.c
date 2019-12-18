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
struct lcd_device {int dummy; } ;

/* Variables and functions */
 int FB_BLANK_UNBLANK ; 
 int /*<<< orphan*/  PPC_LDD2 ; 
 int /*<<< orphan*/  PPDR ; 
 int /*<<< orphan*/  PPSR ; 

__attribute__((used)) static int jornada_lcd_set_power(struct lcd_device *ld, int power)
{
	if (power != FB_BLANK_UNBLANK) {
		PPSR &= ~PPC_LDD2;
		PPDR |= PPC_LDD2;
	} else {
		PPSR |= PPC_LDD2;
	}

	return 0;
}