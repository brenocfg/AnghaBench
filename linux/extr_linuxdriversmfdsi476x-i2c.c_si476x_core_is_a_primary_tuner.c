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
struct si476x_core {scalar_t__ diversity_mode; } ;

/* Variables and functions */
 scalar_t__ SI476X_PHDIV_PRIMARY_ANTENNA ; 
 scalar_t__ SI476X_PHDIV_PRIMARY_COMBINING ; 
 scalar_t__ si476x_core_has_diversity (struct si476x_core*) ; 

bool si476x_core_is_a_primary_tuner(struct si476x_core *core)
{
	return si476x_core_has_diversity(core) &&
		(core->diversity_mode == SI476X_PHDIV_PRIMARY_ANTENNA ||
		 core->diversity_mode == SI476X_PHDIV_PRIMARY_COMBINING);
}