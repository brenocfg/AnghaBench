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
struct TYPE_2__ {unsigned int npins; unsigned int* pins; } ;

/* Variables and functions */
 TYPE_1__* npcm7xx_groups ; 

__attribute__((used)) static int npcm7xx_get_group_pins(struct pinctrl_dev *pctldev,
				  unsigned int selector,
				  const unsigned int **pins,
				  unsigned int *npins)
{
	*npins = npcm7xx_groups[selector].npins;
	*pins  = npcm7xx_groups[selector].pins;

	return 0;
}