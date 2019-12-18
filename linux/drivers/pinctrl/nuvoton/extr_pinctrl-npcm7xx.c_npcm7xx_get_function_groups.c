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
struct TYPE_2__ {unsigned int ngroups; char** groups; } ;

/* Variables and functions */
 TYPE_1__* npcm7xx_funcs ; 

__attribute__((used)) static int npcm7xx_get_function_groups(struct pinctrl_dev *pctldev,
				       unsigned int function,
				       const char * const **groups,
				       unsigned int * const ngroups)
{
	*ngroups = npcm7xx_funcs[function].ngroups;
	*groups	 = npcm7xx_funcs[function].groups;

	return 0;
}