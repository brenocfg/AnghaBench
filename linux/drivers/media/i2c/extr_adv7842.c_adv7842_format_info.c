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
typedef  scalar_t__ u32 ;
struct adv7842_state {int dummy; } ;
struct adv7842_format_info {scalar_t__ code; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct adv7842_format_info const*) ; 
 struct adv7842_format_info const* adv7842_formats ; 

__attribute__((used)) static const struct adv7842_format_info *
adv7842_format_info(struct adv7842_state *state, u32 code)
{
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(adv7842_formats); ++i) {
		if (adv7842_formats[i].code == code)
			return &adv7842_formats[i];
	}

	return NULL;
}