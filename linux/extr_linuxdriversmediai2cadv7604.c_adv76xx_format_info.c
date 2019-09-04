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
typedef  scalar_t__ u32 ;
struct adv76xx_state {TYPE_1__* info; } ;
struct adv76xx_format_info {scalar_t__ code; } ;
struct TYPE_2__ {unsigned int nformats; struct adv76xx_format_info const* formats; } ;

/* Variables and functions */

__attribute__((used)) static const struct adv76xx_format_info *
adv76xx_format_info(struct adv76xx_state *state, u32 code)
{
	unsigned int i;

	for (i = 0; i < state->info->nformats; ++i) {
		if (state->info->formats[i].code == code)
			return &state->info->formats[i];
	}

	return NULL;
}