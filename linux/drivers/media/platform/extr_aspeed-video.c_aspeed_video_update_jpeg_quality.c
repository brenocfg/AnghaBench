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
struct aspeed_video {int jpeg_quality; } ;

/* Variables and functions */
 int FIELD_PREP (int,int) ; 
 int /*<<< orphan*/  VE_COMP_CTRL ; 
 int VE_COMP_CTRL_DCT_CHR ; 
 int VE_COMP_CTRL_DCT_LUM ; 
 int /*<<< orphan*/  aspeed_video_update (struct aspeed_video*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void aspeed_video_update_jpeg_quality(struct aspeed_video *video)
{
	u32 comp_ctrl = FIELD_PREP(VE_COMP_CTRL_DCT_LUM, video->jpeg_quality) |
		FIELD_PREP(VE_COMP_CTRL_DCT_CHR, video->jpeg_quality | 0x10);

	aspeed_video_update(video, VE_COMP_CTRL,
			    VE_COMP_CTRL_DCT_LUM | VE_COMP_CTRL_DCT_CHR,
			    comp_ctrl);
}