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
 char const** atmel_functions ; 

__attribute__((used)) static const char *atmel_pmx_get_function_name(struct pinctrl_dev *pctldev,
					       unsigned selector)
{
	return atmel_functions[selector];
}