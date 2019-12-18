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
struct pinctrl_dev {int dummy; } ;

/* Variables and functions */
#define  PIN_FUNC_1 131 
#define  PIN_FUNC_2 130 
#define  PIN_FUNC_3 129 
#define  PIN_FUNC_4 128 

__attribute__((used)) static const char *sprd_pmx_get_function_name(struct pinctrl_dev *pctldev,
					      unsigned int selector)
{
	switch (selector) {
	case PIN_FUNC_1:
		return "func1";
	case PIN_FUNC_2:
		return "func2";
	case PIN_FUNC_3:
		return "func3";
	case PIN_FUNC_4:
		return "func4";
	default:
		return "null";
	}
}