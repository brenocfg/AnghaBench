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
struct ag71xx {TYPE_1__* dcfg; } ;
typedef  enum ag71xx_type { ____Placeholder_ag71xx_type } ag71xx_type ;
struct TYPE_2__ {int type; } ;

/* Variables and functions */

__attribute__((used)) static bool ag71xx_is(struct ag71xx *ag, enum ag71xx_type type)
{
	return ag->dcfg->type == type;
}