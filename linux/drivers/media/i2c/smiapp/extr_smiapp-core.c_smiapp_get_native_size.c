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
struct v4l2_rect {scalar_t__ height; scalar_t__ width; scalar_t__ left; scalar_t__ top; } ;
struct smiapp_subdev {TYPE_1__* sensor; } ;
struct TYPE_2__ {scalar_t__* limits; } ;

/* Variables and functions */
 size_t SMIAPP_LIMIT_X_ADDR_MAX ; 
 size_t SMIAPP_LIMIT_Y_ADDR_MAX ; 

__attribute__((used)) static void smiapp_get_native_size(struct smiapp_subdev *ssd,
				    struct v4l2_rect *r)
{
	r->top = 0;
	r->left = 0;
	r->width = ssd->sensor->limits[SMIAPP_LIMIT_X_ADDR_MAX] + 1;
	r->height = ssd->sensor->limits[SMIAPP_LIMIT_Y_ADDR_MAX] + 1;
}