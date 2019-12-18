#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pinctrl_dev {int dummy; } ;
struct TYPE_2__ {char const* name; } ;

/* Variables and functions */
 TYPE_1__* artpec6_pmx_functions ; 

__attribute__((used)) static const char *artpec6_pmx_get_fname(struct pinctrl_dev *pctldev,
					 unsigned int function)
{
	return artpec6_pmx_functions[function].name;
}