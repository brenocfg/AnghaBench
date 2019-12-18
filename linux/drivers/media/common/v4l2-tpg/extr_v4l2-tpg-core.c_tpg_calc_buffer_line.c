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
struct TYPE_2__ {scalar_t__ top; } ;
struct tpg_data {int buf_height; TYPE_1__ compose; } ;

/* Variables and functions */
#define  V4L2_FIELD_SEQ_BT 129 
#define  V4L2_FIELD_SEQ_TB 128 

__attribute__((used)) static unsigned tpg_calc_buffer_line(const struct tpg_data *tpg, unsigned y,
				    unsigned field)
{
	y += tpg->compose.top;
	switch (field) {
	case V4L2_FIELD_SEQ_TB:
		if (y & 1)
			return tpg->buf_height / 2 + y / 2;
		return y / 2;
	case V4L2_FIELD_SEQ_BT:
		if (y & 1)
			return y / 2;
		return tpg->buf_height / 2 + y / 2;
	default:
		return y;
	}
}