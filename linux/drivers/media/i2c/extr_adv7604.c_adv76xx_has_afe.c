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
struct adv76xx_state {TYPE_1__* info; } ;
struct TYPE_2__ {int has_afe; } ;

/* Variables and functions */

__attribute__((used)) static bool adv76xx_has_afe(struct adv76xx_state *state)
{
	return state->info->has_afe;
}