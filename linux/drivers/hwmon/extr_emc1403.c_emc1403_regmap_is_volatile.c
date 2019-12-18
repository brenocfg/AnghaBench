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
struct device {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static bool emc1403_regmap_is_volatile(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case 0x00:	/* internal diode high byte */
	case 0x01:	/* external diode 1 high byte */
	case 0x02:	/* status */
	case 0x10:	/* external diode 1 low byte */
	case 0x1b:	/* external diode fault */
	case 0x23:	/* external diode 2 high byte */
	case 0x24:	/* external diode 2 low byte */
	case 0x29:	/* internal diode low byte */
	case 0x2a:	/* externl diode 3 high byte */
	case 0x2b:	/* external diode 3 low byte */
	case 0x35:	/* high limit status */
	case 0x36:	/* low limit status */
	case 0x37:	/* therm limit status */
		return true;
	default:
		return false;
	}
}