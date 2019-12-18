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
typedef  int /*<<< orphan*/  u32 ;
typedef  unsigned int u16 ;
struct tw5864_input {unsigned int* md_threshold_grid_values; } ;
struct TYPE_2__ {scalar_t__ addr; } ;
struct tw5864_h264_frame {TYPE_1__ mv; struct tw5864_input* input; } ;

/* Variables and functions */
 int MD_CELLS ; 
 unsigned int tw5864_md_metric_from_mvd (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tw5864_is_motion_triggered(struct tw5864_h264_frame *frame)
{
	struct tw5864_input *input = frame->input;
	u32 *mv = (u32 *)frame->mv.addr;
	int i;
	int detected = 0;

	for (i = 0; i < MD_CELLS; i++) {
		const u16 thresh = input->md_threshold_grid_values[i];
		const unsigned int metric = tw5864_md_metric_from_mvd(mv[i]);

		if (metric > thresh)
			detected = 1;

		if (detected)
			break;
	}
	return detected;
}