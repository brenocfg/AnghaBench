#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ curr; } ;
struct saa7134_dev {int ts_field; int /*<<< orphan*/  slock; TYPE_1__ ts_q; } ;
typedef  enum v4l2_field { ____Placeholder_v4l2_field } v4l2_field ;

/* Variables and functions */
 int V4L2_FIELD_TOP ; 
 int /*<<< orphan*/  VB2_BUF_STATE_DONE ; 
 int /*<<< orphan*/  saa7134_buffer_finish (struct saa7134_dev*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saa7134_buffer_next (struct saa7134_dev*,TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void saa7134_irq_ts_done(struct saa7134_dev *dev, unsigned long status)
{
	enum v4l2_field field;

	spin_lock(&dev->slock);
	if (dev->ts_q.curr) {
		field = dev->ts_field;
		if (field != V4L2_FIELD_TOP) {
			if ((status & 0x100000) != 0x000000)
				goto done;
		} else {
			if ((status & 0x100000) != 0x100000)
				goto done;
		}
		saa7134_buffer_finish(dev, &dev->ts_q, VB2_BUF_STATE_DONE);
	}
	saa7134_buffer_next(dev,&dev->ts_q);

 done:
	spin_unlock(&dev->slock);
}