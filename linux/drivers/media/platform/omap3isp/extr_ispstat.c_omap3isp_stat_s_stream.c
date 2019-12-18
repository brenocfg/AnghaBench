#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct v4l2_subdev {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct ispstat {TYPE_1__ subdev; TYPE_2__* isp; TYPE_3__* ops; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* enable ) (struct ispstat*,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  stat_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isp_stat_try_enable (struct ispstat*) ; 
 int /*<<< orphan*/  omap3isp_stat_enable (struct ispstat*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap3isp_stat_isr (struct ispstat*) ; 
 int /*<<< orphan*/  omap3isp_stat_pcr_busy (struct ispstat*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct ispstat*,int /*<<< orphan*/ ) ; 
 struct ispstat* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

int omap3isp_stat_s_stream(struct v4l2_subdev *subdev, int enable)
{
	struct ispstat *stat = v4l2_get_subdevdata(subdev);

	if (enable) {
		/*
		 * Only set enable PCR bit if the module was previously
		 * enabled through ioctl.
		 */
		isp_stat_try_enable(stat);
	} else {
		unsigned long flags;
		/* Disable PCR bit and config enable field */
		omap3isp_stat_enable(stat, 0);
		spin_lock_irqsave(&stat->isp->stat_lock, flags);
		stat->ops->enable(stat, 0);
		spin_unlock_irqrestore(&stat->isp->stat_lock, flags);

		/*
		 * If module isn't busy, a new interrupt may come or not to
		 * set the state to DISABLED. As Histogram needs to read its
		 * internal memory to clear it, let interrupt handler
		 * responsible of changing state to DISABLED. If the last
		 * interrupt is coming, it's still safe as the handler will
		 * ignore the second time when state is already set to DISABLED.
		 * It's necessary to synchronize Histogram with streamoff, once
		 * the module may be considered idle before last SDMA transfer
		 * starts if we return here.
		 */
		if (!omap3isp_stat_pcr_busy(stat))
			omap3isp_stat_isr(stat);

		dev_dbg(stat->isp->dev, "%s: module is being disabled\n",
			stat->subdev.name);
	}

	return 0;
}