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
 unsigned int BIT (int) ; 

__attribute__((used)) static unsigned int sprd_pinconf_drive(unsigned int mA)
{
	unsigned int val = 0;

	switch (mA) {
	case 2:
		break;
	case 4:
		val |= BIT(19);
		break;
	case 6:
		val |= BIT(20);
		break;
	case 8:
		val |= BIT(19) | BIT(20);
		break;
	case 10:
		val |= BIT(21);
		break;
	case 12:
		val |= BIT(21) | BIT(19);
		break;
	case 14:
		val |= BIT(21) | BIT(20);
		break;
	case 16:
		val |= BIT(19) | BIT(20) | BIT(21);
		break;
	case 20:
		val |= BIT(22);
		break;
	case 21:
		val |= BIT(22) | BIT(19);
		break;
	case 24:
		val |= BIT(22) | BIT(20);
		break;
	case 25:
		val |= BIT(22) | BIT(20) | BIT(19);
		break;
	case 27:
		val |= BIT(22) | BIT(21);
		break;
	case 29:
		val |= BIT(22) | BIT(21) | BIT(19);
		break;
	case 31:
		val |= BIT(22) | BIT(21) | BIT(20);
		break;
	case 33:
		val |= BIT(22) | BIT(21) | BIT(20) | BIT(19);
		break;
	default:
		break;
	}

	return val;
}