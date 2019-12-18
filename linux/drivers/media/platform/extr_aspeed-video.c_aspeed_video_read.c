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
struct aspeed_video {int /*<<< orphan*/  dev; scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 scalar_t__ readl (scalar_t__) ; 

__attribute__((used)) static u32 aspeed_video_read(struct aspeed_video *video, u32 reg)
{
	u32 t = readl(video->base + reg);

	dev_dbg(video->dev, "read %03x[%08x]\n", reg, t);
	return t;
}