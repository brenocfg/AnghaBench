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
struct TYPE_2__ {char** groups; unsigned int num_groups; } ;

/* Variables and functions */
 TYPE_1__* gemini_pmx_functions ; 

__attribute__((used)) static int gemini_pmx_get_groups(struct pinctrl_dev *pctldev,
				 unsigned int selector,
				 const char * const **groups,
				 unsigned int * const num_groups)
{
	*groups = gemini_pmx_functions[selector].groups;
	*num_groups = gemini_pmx_functions[selector].num_groups;
	return 0;
}