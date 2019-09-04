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
struct TYPE_2__ {int /*<<< orphan*/  timeout; } ;
struct saa7134_dev {scalar_t__ ts_field; int /*<<< orphan*/  ts_started; TYPE_1__ ts_q; } ;
struct saa7134_buf {scalar_t__ top_seen; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAA7134_RS_BA1 (int) ; 
 int /*<<< orphan*/  SAA7134_RS_BA2 (int) ; 
 scalar_t__ TS_BUFFER_TIMEOUT ; 
 scalar_t__ V4L2_FIELD_BOTTOM ; 
 scalar_t__ V4L2_FIELD_TOP ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  saa7134_buffer_base (struct saa7134_buf*) ; 
 int /*<<< orphan*/  saa7134_set_dmabits (struct saa7134_dev*) ; 
 int /*<<< orphan*/  saa7134_ts_start (struct saa7134_dev*) ; 
 int /*<<< orphan*/  saa_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_dbg (char*,struct saa7134_buf*,...) ; 

__attribute__((used)) static int buffer_activate(struct saa7134_dev *dev,
			   struct saa7134_buf *buf,
			   struct saa7134_buf *next)
{

	ts_dbg("buffer_activate [%p]", buf);
	buf->top_seen = 0;

	if (!dev->ts_started)
		dev->ts_field = V4L2_FIELD_TOP;

	if (NULL == next)
		next = buf;
	if (V4L2_FIELD_TOP == dev->ts_field) {
		ts_dbg("- [top]     buf=%p next=%p\n", buf, next);
		saa_writel(SAA7134_RS_BA1(5),saa7134_buffer_base(buf));
		saa_writel(SAA7134_RS_BA2(5),saa7134_buffer_base(next));
		dev->ts_field = V4L2_FIELD_BOTTOM;
	} else {
		ts_dbg("- [bottom]  buf=%p next=%p\n", buf, next);
		saa_writel(SAA7134_RS_BA1(5),saa7134_buffer_base(next));
		saa_writel(SAA7134_RS_BA2(5),saa7134_buffer_base(buf));
		dev->ts_field = V4L2_FIELD_TOP;
	}

	/* start DMA */
	saa7134_set_dmabits(dev);

	mod_timer(&dev->ts_q.timeout, jiffies+TS_BUFFER_TIMEOUT);

	if (!dev->ts_started)
		saa7134_ts_start(dev);

	return 0;
}