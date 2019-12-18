#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct omap3isp_stat_data {int /*<<< orphan*/  buf_size; int /*<<< orphan*/  frame_number; int /*<<< orphan*/  config_counter; TYPE_3__ ts; } ;
struct TYPE_8__ {int tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct ispstat_buffer {int empty; int /*<<< orphan*/  buf_size; int /*<<< orphan*/  frame_number; int /*<<< orphan*/  config_counter; TYPE_4__ ts; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
struct ispstat {scalar_t__ state; int /*<<< orphan*/  ioctl_lock; TYPE_2__ subdev; TYPE_1__* isp; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ ISPSTAT_ENABLED ; 
 scalar_t__ IS_ERR (struct ispstat_buffer*) ; 
 int NSEC_PER_USEC ; 
 int PTR_ERR (struct ispstat_buffer*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct ispstat_buffer* isp_stat_buf_get (struct ispstat*,struct omap3isp_stat_data*) ; 
 int /*<<< orphan*/  isp_stat_buf_release (struct ispstat*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int omap3isp_stat_request_statistics(struct ispstat *stat,
				     struct omap3isp_stat_data *data)
{
	struct ispstat_buffer *buf;

	if (stat->state != ISPSTAT_ENABLED) {
		dev_dbg(stat->isp->dev, "%s: engine not enabled.\n",
			stat->subdev.name);
		return -EINVAL;
	}

	mutex_lock(&stat->ioctl_lock);
	buf = isp_stat_buf_get(stat, data);
	if (IS_ERR(buf)) {
		mutex_unlock(&stat->ioctl_lock);
		return PTR_ERR(buf);
	}

	data->ts.tv_sec = buf->ts.tv_sec;
	data->ts.tv_usec = buf->ts.tv_nsec / NSEC_PER_USEC;
	data->config_counter = buf->config_counter;
	data->frame_number = buf->frame_number;
	data->buf_size = buf->buf_size;

	buf->empty = 1;
	isp_stat_buf_release(stat);
	mutex_unlock(&stat->ioctl_lock);

	return 0;
}