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
struct v4l2_subdev {int dummy; } ;
struct fimc_source_info {int dummy; } ;
struct fimc_sensor_info {int /*<<< orphan*/  host; } ;
struct fimc_md {int /*<<< orphan*/  slock; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 
 struct fimc_sensor_info* source_to_sensor_info (struct fimc_source_info*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct fimc_source_info* v4l2_get_subdev_hostdata (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static void __setup_sensor_notification(struct fimc_md *fmd,
					struct v4l2_subdev *sensor,
					struct v4l2_subdev *fimc_sd)
{
	struct fimc_source_info *src_inf;
	struct fimc_sensor_info *md_si;
	unsigned long flags;

	src_inf = v4l2_get_subdev_hostdata(sensor);
	if (!src_inf || WARN_ON(fmd == NULL))
		return;

	md_si = source_to_sensor_info(src_inf);
	spin_lock_irqsave(&fmd->slock, flags);
	md_si->host = v4l2_get_subdevdata(fimc_sd);
	spin_unlock_irqrestore(&fmd->slock, flags);
}