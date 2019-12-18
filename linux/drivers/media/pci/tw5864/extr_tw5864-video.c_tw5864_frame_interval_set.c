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
struct tw5864_input {scalar_t__ std; int /*<<< orphan*/  nr; scalar_t__ frame_interval; struct tw5864_dev* root; } ;
struct tw5864_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ STD_NTSC ; 
 int /*<<< orphan*/  TW5864_H264EN_RATE_CNTL_HI_WORD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TW5864_H264EN_RATE_CNTL_LO_WORD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tw_writel (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void tw5864_frame_interval_set(struct tw5864_input *input)
{
	/*
	 * This register value seems to follow such approach: In each second
	 * interval, when processing Nth frame, it checks Nth bit of register
	 * value and, if the bit is 1, it processes the frame, otherwise the
	 * frame is discarded.
	 * So unary representation would work, but more or less equal gaps
	 * between the frames should be preserved.
	 *
	 * For 1 FPS - 0x00000001
	 * 00000000 00000000 00000000 00000001
	 *
	 * For max FPS - set all 25/30 lower bits:
	 * 00111111 11111111 11111111 11111111 (NTSC)
	 * 00000001 11111111 11111111 11111111 (PAL)
	 *
	 * For half of max FPS - use such pattern:
	 * 00010101 01010101 01010101 01010101 (NTSC)
	 * 00000001 01010101 01010101 01010101 (PAL)
	 *
	 * Et cetera.
	 *
	 * The value supplied to hardware is capped by mask of 25/30 lower bits.
	 */
	struct tw5864_dev *dev = input->root;
	u32 unary_framerate = 0;
	int shift = 0;
	int std_max_fps = input->std == STD_NTSC ? 30 : 25;

	for (shift = 0; shift < std_max_fps; shift += input->frame_interval)
		unary_framerate |= 0x00000001 << shift;

	tw_writel(TW5864_H264EN_RATE_CNTL_LO_WORD(input->nr, 0),
		  unary_framerate >> 16);
	tw_writel(TW5864_H264EN_RATE_CNTL_HI_WORD(input->nr, 0),
		  unary_framerate & 0xffff);
}