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
struct rvin_video_format {scalar_t__ fourcc; } ;
struct rvin_dev {TYPE_1__* info; } ;
struct TYPE_2__ {scalar_t__ model; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct rvin_video_format const*) ; 
 scalar_t__ RCAR_M1 ; 
 scalar_t__ V4L2_PIX_FMT_XBGR32 ; 
 struct rvin_video_format const* rvin_formats ; 

const struct rvin_video_format *rvin_format_from_pixel(struct rvin_dev *vin,
						       u32 pixelformat)
{
	int i;

	if (vin->info->model == RCAR_M1 && pixelformat == V4L2_PIX_FMT_XBGR32)
		return NULL;

	for (i = 0; i < ARRAY_SIZE(rvin_formats); i++)
		if (rvin_formats[i].fourcc == pixelformat)
			return rvin_formats + i;

	return NULL;
}