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
struct videomode {int vfront_porch; int vback_porch; int vsync_len; } ;
struct ipu_di {TYPE_1__* ipu; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 

int ipu_di_adjust_videomode(struct ipu_di *di, struct videomode *mode)
{
	u32 diff;

	if (mode->vfront_porch >= 2)
		return 0;

	diff = 2 - mode->vfront_porch;

	if (mode->vback_porch >= diff) {
		mode->vfront_porch = 2;
		mode->vback_porch -= diff;
	} else if (mode->vsync_len > diff) {
		mode->vfront_porch = 2;
		mode->vsync_len = mode->vsync_len - diff;
	} else {
		dev_warn(di->ipu->dev, "failed to adjust videomode\n");
		return -EINVAL;
	}

	dev_dbg(di->ipu->dev, "videomode adapted for IPU restrictions\n");
	return 0;
}