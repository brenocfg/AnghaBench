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
typedef  int u32 ;
struct radeon_device {scalar_t__ family; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ CHIP_RV740 ; 
 int r600_count_pipe_bits (int) ; 

u32 r6xx_remap_render_backend(struct radeon_device *rdev,
			      u32 tiling_pipe_num,
			      u32 max_rb_num,
			      u32 total_max_rb_num,
			      u32 disabled_rb_mask)
{
	u32 rendering_pipe_num, rb_num_width, req_rb_num;
	u32 pipe_rb_ratio, pipe_rb_remain, tmp;
	u32 data = 0, mask = 1 << (max_rb_num - 1);
	unsigned i, j;

	/* mask out the RBs that don't exist on that asic */
	tmp = disabled_rb_mask | ((0xff << max_rb_num) & 0xff);
	/* make sure at least one RB is available */
	if ((tmp & 0xff) != 0xff)
		disabled_rb_mask = tmp;

	rendering_pipe_num = 1 << tiling_pipe_num;
	req_rb_num = total_max_rb_num - r600_count_pipe_bits(disabled_rb_mask);
	BUG_ON(rendering_pipe_num < req_rb_num);

	pipe_rb_ratio = rendering_pipe_num / req_rb_num;
	pipe_rb_remain = rendering_pipe_num - pipe_rb_ratio * req_rb_num;

	if (rdev->family <= CHIP_RV740) {
		/* r6xx/r7xx */
		rb_num_width = 2;
	} else {
		/* eg+ */
		rb_num_width = 4;
	}

	for (i = 0; i < max_rb_num; i++) {
		if (!(mask & disabled_rb_mask)) {
			for (j = 0; j < pipe_rb_ratio; j++) {
				data <<= rb_num_width;
				data |= max_rb_num - i - 1;
			}
			if (pipe_rb_remain) {
				data <<= rb_num_width;
				data |= max_rb_num - i - 1;
				pipe_rb_remain--;
			}
		}
		mask >>= 1;
	}

	return data;
}