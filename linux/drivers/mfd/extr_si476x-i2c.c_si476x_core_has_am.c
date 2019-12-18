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
struct si476x_core {scalar_t__ chip_id; } ;

/* Variables and functions */
 scalar_t__ SI476X_CHIP_SI4761 ; 
 scalar_t__ SI476X_CHIP_SI4764 ; 

bool si476x_core_has_am(struct si476x_core *core)
{
	return core->chip_id == SI476X_CHIP_SI4761 ||
		core->chip_id == SI476X_CHIP_SI4764;
}