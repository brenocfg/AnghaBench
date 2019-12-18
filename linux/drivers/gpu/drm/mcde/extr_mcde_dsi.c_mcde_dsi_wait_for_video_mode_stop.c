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
struct mcde_dsi {int /*<<< orphan*/  dev; scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ DSI_VID_MODE_STS ; 
 int DSI_VID_MODE_STS_VSG_RUNNING ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void mcde_dsi_wait_for_video_mode_stop(struct mcde_dsi *d)
{
	u32 val;
	int i;

	/* Wait until we get out og video mode */
	i = 0;
	val = DSI_VID_MODE_STS_VSG_RUNNING;
	while ((readl(d->regs + DSI_VID_MODE_STS) & val) == val) {
		/* Sleep for a millisecond */
		usleep_range(1000, 2000);
		if (i++ == 100) {
			dev_warn(d->dev,
				 "could not get out of video mode\n");
			return;
		}
	}
}