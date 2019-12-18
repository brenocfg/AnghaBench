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
typedef  scalar_t__ u32 ;
struct aspeed_video {scalar_t__ base; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void aspeed_video_update(struct aspeed_video *video, u32 reg, u32 clear,
				u32 bits)
{
	u32 t = readl(video->base + reg);
	u32 before = t;

	t &= ~clear;
	t |= bits;
	writel(t, video->base + reg);
	dev_dbg(video->dev, "update %03x[%08x -> %08x]\n", reg, before,
		readl(video->base + reg));
}