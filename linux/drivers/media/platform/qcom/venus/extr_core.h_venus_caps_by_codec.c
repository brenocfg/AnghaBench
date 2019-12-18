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
struct venus_core {unsigned int codecs_count; struct venus_caps* caps; } ;
struct venus_caps {scalar_t__ codec; scalar_t__ domain; } ;

/* Variables and functions */

__attribute__((used)) static inline struct venus_caps *
venus_caps_by_codec(struct venus_core *core, u32 codec, u32 domain)
{
	unsigned int c;

	for (c = 0; c < core->codecs_count; c++) {
		if (core->caps[c].codec == codec &&
		    core->caps[c].domain == domain)
			return &core->caps[c];
	}

	return NULL;
}