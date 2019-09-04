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
#define  WM831X_AUXADC_DATA 148 
#define  WM831X_CHARGER_STATUS 147 
#define  WM831X_DCDC_STATUS 146 
#define  WM831X_DCDC_UV_STATUS 145 
#define  WM831X_GPIO_LEVEL 144 
#define  WM831X_INTERRUPT_STATUS_1 143 
#define  WM831X_INTERRUPT_STATUS_2 142 
#define  WM831X_INTERRUPT_STATUS_3 141 
#define  WM831X_INTERRUPT_STATUS_4 140 
#define  WM831X_INTERRUPT_STATUS_5 139 
#define  WM831X_LDO_STATUS 138 
#define  WM831X_LDO_UV_STATUS 137 
#define  WM831X_OFF_SOURCE 136 
#define  WM831X_ON_SOURCE 135 
#define  WM831X_RTC_TIME_1 134 
#define  WM831X_RTC_TIME_2 133 
#define  WM831X_SYSTEM_INTERRUPTS 132 
#define  WM831X_SYSTEM_STATUS 131 
#define  WM831X_TOUCH_DATA_X 130 
#define  WM831X_TOUCH_DATA_Y 129 
#define  WM831X_TOUCH_DATA_Z 128 

__attribute__((used)) static bool wm831x_reg_volatile(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case WM831X_SYSTEM_STATUS:
	case WM831X_ON_SOURCE:
	case WM831X_OFF_SOURCE:
	case WM831X_GPIO_LEVEL:
	case WM831X_SYSTEM_INTERRUPTS:
	case WM831X_INTERRUPT_STATUS_1:
	case WM831X_INTERRUPT_STATUS_2:
	case WM831X_INTERRUPT_STATUS_3:
	case WM831X_INTERRUPT_STATUS_4:
	case WM831X_INTERRUPT_STATUS_5:
	case WM831X_RTC_TIME_1:
	case WM831X_RTC_TIME_2:
	case WM831X_TOUCH_DATA_X:
	case WM831X_TOUCH_DATA_Y:
	case WM831X_TOUCH_DATA_Z:
	case WM831X_AUXADC_DATA:
	case WM831X_CHARGER_STATUS:
	case WM831X_DCDC_STATUS:
	case WM831X_LDO_STATUS:
	case WM831X_DCDC_UV_STATUS:
	case WM831X_LDO_UV_STATUS:
		return true;
	default:
		return false;
	}
}