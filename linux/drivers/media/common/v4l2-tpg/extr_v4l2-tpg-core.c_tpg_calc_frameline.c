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
struct TYPE_2__ {unsigned int top; } ;
struct tpg_data {TYPE_1__ crop; } ;

/* Variables and functions */
#define  V4L2_FIELD_BOTTOM 129 
#define  V4L2_FIELD_TOP 128 

__attribute__((used)) static unsigned tpg_calc_frameline(const struct tpg_data *tpg, unsigned src_y,
				    unsigned field)
{
	switch (field) {
	case V4L2_FIELD_TOP:
		return tpg->crop.top + src_y * 2;
	case V4L2_FIELD_BOTTOM:
		return tpg->crop.top + src_y * 2 + 1;
	default:
		return src_y + tpg->crop.top;
	}
}