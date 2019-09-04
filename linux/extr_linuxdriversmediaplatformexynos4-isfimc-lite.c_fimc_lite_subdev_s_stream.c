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
struct v4l2_subdev {int /*<<< orphan*/  entity; } ;
struct fimc_lite {int /*<<< orphan*/  lock; int /*<<< orphan*/  state; int /*<<< orphan*/  irq_queue; int /*<<< orphan*/  slock; int /*<<< orphan*/  out_path; int /*<<< orphan*/  sensor; } ;

/* Variables and functions */
 int ENOIOCTLCMD ; 
 scalar_t__ FIMC_IO_ISP ; 
 int /*<<< orphan*/  ST_FLITE_OFF ; 
 int /*<<< orphan*/  ST_FLITE_RUN ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fimc_find_remote_sensor (int /*<<< orphan*/ *) ; 
 int fimc_lite_hw_init (struct fimc_lite*,int) ; 
 int /*<<< orphan*/  flite_hw_capture_start (struct fimc_lite*) ; 
 int /*<<< orphan*/  flite_hw_capture_stop (struct fimc_lite*) ; 
 int /*<<< orphan*/  flite_hw_reset (struct fimc_lite*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_err (struct v4l2_subdev*,char*) ; 
 struct fimc_lite* v4l2_get_subdevdata (struct v4l2_subdev*) ; 
 int wait_event_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fimc_lite_subdev_s_stream(struct v4l2_subdev *sd, int on)
{
	struct fimc_lite *fimc = v4l2_get_subdevdata(sd);
	unsigned long flags;
	int ret;

	/*
	 * Find sensor subdev linked to FIMC-LITE directly or through
	 * MIPI-CSIS. This is required for configuration where FIMC-LITE
	 * is used as a subdev only and feeds data internally to FIMC-IS.
	 * The pipeline links are protected through entity.stream_count
	 * so there is no need to take the media graph mutex here.
	 */
	fimc->sensor = fimc_find_remote_sensor(&sd->entity);

	if (atomic_read(&fimc->out_path) != FIMC_IO_ISP)
		return -ENOIOCTLCMD;

	mutex_lock(&fimc->lock);
	if (on) {
		flite_hw_reset(fimc);
		ret = fimc_lite_hw_init(fimc, true);
		if (!ret) {
			spin_lock_irqsave(&fimc->slock, flags);
			flite_hw_capture_start(fimc);
			spin_unlock_irqrestore(&fimc->slock, flags);
		}
	} else {
		set_bit(ST_FLITE_OFF, &fimc->state);

		spin_lock_irqsave(&fimc->slock, flags);
		flite_hw_capture_stop(fimc);
		spin_unlock_irqrestore(&fimc->slock, flags);

		ret = wait_event_timeout(fimc->irq_queue,
				!test_bit(ST_FLITE_OFF, &fimc->state),
				msecs_to_jiffies(200));
		if (ret == 0)
			v4l2_err(sd, "s_stream(0) timeout\n");
		clear_bit(ST_FLITE_RUN, &fimc->state);
	}

	mutex_unlock(&fimc->lock);
	return ret;
}