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
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
struct ispstat {TYPE_3__* active_buf; int /*<<< orphan*/  frame_number; int /*<<< orphan*/  config_counter; TYPE_2__ subdev; TYPE_1__* isp; int /*<<< orphan*/  buf_size; } ;
struct TYPE_6__ {scalar_t__ empty; int /*<<< orphan*/  frame_number; int /*<<< orphan*/  config_counter; int /*<<< orphan*/  buf_size; int /*<<< orphan*/  ts; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int STAT_BUF_DONE ; 
 int STAT_NO_BUF ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ isp_stat_buf_check_magic (struct ispstat*,TYPE_3__*) ; 
 int /*<<< orphan*/  ktime_get_ts64 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int isp_stat_buf_queue(struct ispstat *stat)
{
	if (!stat->active_buf)
		return STAT_NO_BUF;

	ktime_get_ts64(&stat->active_buf->ts);

	stat->active_buf->buf_size = stat->buf_size;
	if (isp_stat_buf_check_magic(stat, stat->active_buf)) {
		dev_dbg(stat->isp->dev, "%s: data wasn't properly written.\n",
			stat->subdev.name);
		return STAT_NO_BUF;
	}
	stat->active_buf->config_counter = stat->config_counter;
	stat->active_buf->frame_number = stat->frame_number;
	stat->active_buf->empty = 0;
	stat->active_buf = NULL;

	return STAT_BUF_DONE;
}