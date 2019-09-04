#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct omap3isp_stat_data {scalar_t__ buf_size; int /*<<< orphan*/  buf; } ;
struct ispstat_buffer {int empty; scalar_t__ buf_size; int /*<<< orphan*/  virt_addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct ispstat {TYPE_2__ subdev; TYPE_1__* isp; struct ispstat_buffer* locked_buf; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  stat_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  EBUSY ; 
 int /*<<< orphan*/  EFAULT ; 
 int /*<<< orphan*/  EINVAL ; 
 struct ispstat_buffer* ERR_PTR (int /*<<< orphan*/ ) ; 
 int copy_to_user (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ isp_stat_buf_check_magic (struct ispstat*,struct ispstat_buffer*) ; 
 struct ispstat_buffer* isp_stat_buf_find_oldest (struct ispstat*) ; 
 int /*<<< orphan*/  isp_stat_buf_release (struct ispstat*) ; 
 int /*<<< orphan*/  isp_stat_buf_sync_for_cpu (struct ispstat*,struct ispstat_buffer*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct ispstat_buffer *isp_stat_buf_get(struct ispstat *stat,
					       struct omap3isp_stat_data *data)
{
	int rval = 0;
	unsigned long flags;
	struct ispstat_buffer *buf;

	spin_lock_irqsave(&stat->isp->stat_lock, flags);

	while (1) {
		buf = isp_stat_buf_find_oldest(stat);
		if (!buf) {
			spin_unlock_irqrestore(&stat->isp->stat_lock, flags);
			dev_dbg(stat->isp->dev, "%s: cannot find a buffer.\n",
				stat->subdev.name);
			return ERR_PTR(-EBUSY);
		}
		if (isp_stat_buf_check_magic(stat, buf)) {
			dev_dbg(stat->isp->dev,
				"%s: current buffer has corrupted data\n.",
				stat->subdev.name);
			/* Mark empty because it doesn't have valid data. */
			buf->empty = 1;
		} else {
			/* Buffer isn't corrupted. */
			break;
		}
	}

	stat->locked_buf = buf;

	spin_unlock_irqrestore(&stat->isp->stat_lock, flags);

	if (buf->buf_size > data->buf_size) {
		dev_warn(stat->isp->dev,
			 "%s: userspace's buffer size is not enough.\n",
			 stat->subdev.name);
		isp_stat_buf_release(stat);
		return ERR_PTR(-EINVAL);
	}

	isp_stat_buf_sync_for_cpu(stat, buf);

	rval = copy_to_user(data->buf,
			    buf->virt_addr,
			    buf->buf_size);

	if (rval) {
		dev_info(stat->isp->dev,
			 "%s: failed copying %d bytes of stat data\n",
			 stat->subdev.name, rval);
		buf = ERR_PTR(-EFAULT);
		isp_stat_buf_release(stat);
	}

	return buf;
}