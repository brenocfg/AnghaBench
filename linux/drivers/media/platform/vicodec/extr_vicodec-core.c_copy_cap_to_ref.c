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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/ * buf; } ;
struct v4l2_fwht_state {unsigned int stride; unsigned int ref_stride; unsigned int visible_height; unsigned int coded_height; TYPE_1__ ref_frame; } ;
struct v4l2_fwht_pixfmt_info {int planes_num; int height_div; scalar_t__ id; } ;

/* Variables and functions */
 scalar_t__ V4L2_PIX_FMT_NV24 ; 
 scalar_t__ V4L2_PIX_FMT_NV42 ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int) ; 

__attribute__((used)) static void copy_cap_to_ref(const u8 *cap, const struct v4l2_fwht_pixfmt_info *info,
		struct v4l2_fwht_state *state)
{
	int plane_idx;
	u8 *p_ref = state->ref_frame.buf;
	unsigned int cap_stride = state->stride;
	unsigned int ref_stride = state->ref_stride;

	for (plane_idx = 0; plane_idx < info->planes_num; plane_idx++) {
		int i;
		unsigned int h_div = (plane_idx == 1 || plane_idx == 2) ?
			info->height_div : 1;
		const u8 *row_cap = cap;
		u8 *row_ref = p_ref;

		if (info->planes_num == 3 && plane_idx == 1) {
			cap_stride /= 2;
			ref_stride /= 2;
		}

		if (plane_idx == 1 &&
		    (info->id == V4L2_PIX_FMT_NV24 ||
		     info->id == V4L2_PIX_FMT_NV42)) {
			cap_stride *= 2;
			ref_stride *= 2;
		}

		for (i = 0; i < state->visible_height / h_div; i++) {
			memcpy(row_ref, row_cap, ref_stride);
			row_ref += ref_stride;
			row_cap += cap_stride;
		}
		cap += cap_stride * (state->coded_height / h_div);
		p_ref += ref_stride * (state->coded_height / h_div);
	}
}