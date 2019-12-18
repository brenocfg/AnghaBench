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
typedef  int u32 ;
struct TYPE_2__ {int dma; } ;
struct aspeed_video {int jpeg_quality; int frame_rate; TYPE_1__ jpeg; scalar_t__ yuv420; } ;

/* Variables and functions */
 int FIELD_PREP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  VE_COMP_CTRL ; 
 int /*<<< orphan*/  VE_COMP_CTRL_DCT_CHR ; 
 int /*<<< orphan*/  VE_COMP_CTRL_DCT_LUM ; 
 int VE_COMP_CTRL_RSVD ; 
 int /*<<< orphan*/  VE_COMP_OFFSET ; 
 int /*<<< orphan*/  VE_COMP_PROC_OFFSET ; 
 int /*<<< orphan*/  VE_CTRL ; 
 int VE_CTRL_AUTO_OR_CURSOR ; 
 int /*<<< orphan*/  VE_CTRL_FRC ; 
 int /*<<< orphan*/  VE_INTERRUPT_CTRL ; 
 int /*<<< orphan*/  VE_INTERRUPT_STATUS ; 
 int /*<<< orphan*/  VE_JPEG_ADDR ; 
 int /*<<< orphan*/  VE_MODE_DETECT ; 
 int /*<<< orphan*/  VE_PROTECTION_KEY ; 
 int VE_PROTECTION_KEY_UNLOCK ; 
 int /*<<< orphan*/  VE_SCALING_FACTOR ; 
 int /*<<< orphan*/  VE_SCALING_FILTER0 ; 
 int /*<<< orphan*/  VE_SCALING_FILTER1 ; 
 int /*<<< orphan*/  VE_SCALING_FILTER2 ; 
 int /*<<< orphan*/  VE_SCALING_FILTER3 ; 
 int /*<<< orphan*/  VE_SEQ_CTRL ; 
 int VE_SEQ_CTRL_JPEG_MODE ; 
 int VE_SEQ_CTRL_YUV420 ; 
 int /*<<< orphan*/  aspeed_video_write (struct aspeed_video*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void aspeed_video_init_regs(struct aspeed_video *video)
{
	u32 comp_ctrl = VE_COMP_CTRL_RSVD |
		FIELD_PREP(VE_COMP_CTRL_DCT_LUM, video->jpeg_quality) |
		FIELD_PREP(VE_COMP_CTRL_DCT_CHR, video->jpeg_quality | 0x10);
	u32 ctrl = VE_CTRL_AUTO_OR_CURSOR;
	u32 seq_ctrl = VE_SEQ_CTRL_JPEG_MODE;

	if (video->frame_rate)
		ctrl |= FIELD_PREP(VE_CTRL_FRC, video->frame_rate);

	if (video->yuv420)
		seq_ctrl |= VE_SEQ_CTRL_YUV420;

	/* Unlock VE registers */
	aspeed_video_write(video, VE_PROTECTION_KEY, VE_PROTECTION_KEY_UNLOCK);

	/* Disable interrupts */
	aspeed_video_write(video, VE_INTERRUPT_CTRL, 0);
	aspeed_video_write(video, VE_INTERRUPT_STATUS, 0xffffffff);

	/* Clear the offset */
	aspeed_video_write(video, VE_COMP_PROC_OFFSET, 0);
	aspeed_video_write(video, VE_COMP_OFFSET, 0);

	aspeed_video_write(video, VE_JPEG_ADDR, video->jpeg.dma);

	/* Set control registers */
	aspeed_video_write(video, VE_SEQ_CTRL, seq_ctrl);
	aspeed_video_write(video, VE_CTRL, ctrl);
	aspeed_video_write(video, VE_COMP_CTRL, comp_ctrl);

	/* Don't downscale */
	aspeed_video_write(video, VE_SCALING_FACTOR, 0x10001000);
	aspeed_video_write(video, VE_SCALING_FILTER0, 0x00200000);
	aspeed_video_write(video, VE_SCALING_FILTER1, 0x00200000);
	aspeed_video_write(video, VE_SCALING_FILTER2, 0x00200000);
	aspeed_video_write(video, VE_SCALING_FILTER3, 0x00200000);

	/* Set mode detection defaults */
	aspeed_video_write(video, VE_MODE_DETECT, 0x22666500);
}