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
struct aspeed_video {int /*<<< orphan*/  flags; int /*<<< orphan*/  eclk; int /*<<< orphan*/  vclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  VE_INTERRUPT_CTRL ; 
 int /*<<< orphan*/  VE_INTERRUPT_STATUS ; 
 int /*<<< orphan*/  VIDEO_CLOCKS_ON ; 
 int /*<<< orphan*/  aspeed_video_write (struct aspeed_video*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void aspeed_video_off(struct aspeed_video *video)
{
	if (!test_bit(VIDEO_CLOCKS_ON, &video->flags))
		return;

	/* Disable interrupts */
	aspeed_video_write(video, VE_INTERRUPT_CTRL, 0);
	aspeed_video_write(video, VE_INTERRUPT_STATUS, 0xffffffff);

	/* Turn off the relevant clocks */
	clk_disable(video->vclk);
	clk_disable(video->eclk);

	clear_bit(VIDEO_CLOCKS_ON, &video->flags);
}