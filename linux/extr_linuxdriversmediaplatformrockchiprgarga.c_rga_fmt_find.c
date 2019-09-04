#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ pixelformat; } ;
struct TYPE_4__ {TYPE_1__ pix; } ;
struct v4l2_format {TYPE_2__ fmt; } ;
struct rga_fmt {scalar_t__ fourcc; } ;

/* Variables and functions */
 unsigned int NUM_FORMATS ; 
 struct rga_fmt* formats ; 

__attribute__((used)) static struct rga_fmt *rga_fmt_find(struct v4l2_format *f)
{
	unsigned int i;

	for (i = 0; i < NUM_FORMATS; i++) {
		if (formats[i].fourcc == f->fmt.pix.pixelformat)
			return &formats[i];
	}
	return NULL;
}