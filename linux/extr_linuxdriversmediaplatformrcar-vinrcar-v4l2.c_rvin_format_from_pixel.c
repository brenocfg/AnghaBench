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
struct rvin_video_format {scalar_t__ fourcc; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct rvin_video_format const*) ; 
 struct rvin_video_format const* rvin_formats ; 

const struct rvin_video_format *rvin_format_from_pixel(u32 pixelformat)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(rvin_formats); i++)
		if (rvin_formats[i].fourcc == pixelformat)
			return rvin_formats + i;

	return NULL;
}