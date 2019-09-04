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
#define  WM8350_COMPARATOR_INT_STATUS 135 
#define  WM8350_GPIO_INT_STATUS 134 
#define  WM8350_INT_STATUS_1 133 
#define  WM8350_INT_STATUS_2 132 
#define  WM8350_OVER_CURRENT_INT_STATUS 131 
#define  WM8350_POWER_UP_INT_STATUS 130 
#define  WM8350_SYSTEM_INTERRUPTS 129 
#define  WM8350_UNDER_VOLTAGE_INT_STATUS 128 

__attribute__((used)) static bool wm8350_precious(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case WM8350_SYSTEM_INTERRUPTS:
	case WM8350_INT_STATUS_1:
	case WM8350_INT_STATUS_2:
	case WM8350_POWER_UP_INT_STATUS:
	case WM8350_UNDER_VOLTAGE_INT_STATUS:
	case WM8350_OVER_CURRENT_INT_STATUS:
	case WM8350_GPIO_INT_STATUS:
	case WM8350_COMPARATOR_INT_STATUS:
		return true;

	default:
		return false;
	}
}