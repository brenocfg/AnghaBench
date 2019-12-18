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
struct aspeed_video {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VE_INTERRUPT_CTRL ; 
 int /*<<< orphan*/  VE_INTERRUPT_MODE_DETECT ; 
 int /*<<< orphan*/  VE_SEQ_CTRL ; 
 int /*<<< orphan*/  VE_SEQ_CTRL_TRIG_MODE_DET ; 
 int /*<<< orphan*/  aspeed_video_update (struct aspeed_video*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void aspeed_video_enable_mode_detect(struct aspeed_video *video)
{
	/* Enable mode detect interrupts */
	aspeed_video_update(video, VE_INTERRUPT_CTRL, 0,
			    VE_INTERRUPT_MODE_DETECT);

	/* Trigger mode detect */
	aspeed_video_update(video, VE_SEQ_CTRL, 0, VE_SEQ_CTRL_TRIG_MODE_DET);
}