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
typedef  int /*<<< orphan*/  u32 ;
struct v4l2_fwht_pixfmt_info {int dummy; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct v4l2_fwht_pixfmt_info const*) ; 
 struct v4l2_fwht_pixfmt_info const* v4l2_fwht_pixfmts ; 
 int v4l2_fwht_validate_fmt (struct v4l2_fwht_pixfmt_info const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

const struct v4l2_fwht_pixfmt_info *v4l2_fwht_find_nth_fmt(u32 width_div,
							  u32 height_div,
							  u32 components_num,
							  u32 pixenc,
							  unsigned int start_idx)
{
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(v4l2_fwht_pixfmts); i++) {
		bool is_valid = v4l2_fwht_validate_fmt(&v4l2_fwht_pixfmts[i],
						       width_div, height_div,
						       components_num, pixenc);
		if (is_valid) {
			if (start_idx == 0)
				return v4l2_fwht_pixfmts + i;
			start_idx--;
		}
	}
	return NULL;
}