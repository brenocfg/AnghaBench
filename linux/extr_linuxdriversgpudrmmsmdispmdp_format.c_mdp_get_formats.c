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
typedef  size_t uint32_t ;
struct TYPE_2__ {size_t pixel_format; } ;
struct mdp_format {TYPE_1__ base; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (struct mdp_format*) ; 
 scalar_t__ MDP_FORMAT_IS_YUV (struct mdp_format const*) ; 
 struct mdp_format* formats ; 

uint32_t mdp_get_formats(uint32_t *pixel_formats, uint32_t max_formats,
		bool rgb_only)
{
	uint32_t i;
	for (i = 0; i < ARRAY_SIZE(formats); i++) {
		const struct mdp_format *f = &formats[i];

		if (i == max_formats)
			break;

		if (rgb_only && MDP_FORMAT_IS_YUV(f))
			break;

		pixel_formats[i] = f->base.pixel_format;
	}

	return i;
}