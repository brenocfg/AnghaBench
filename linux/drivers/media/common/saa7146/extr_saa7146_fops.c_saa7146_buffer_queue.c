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
struct saa7146_dmaqueue {int /*<<< orphan*/  queue; struct saa7146_buf* curr; } ;
struct saa7146_dev {int /*<<< orphan*/  slock; } ;
struct TYPE_2__ {int /*<<< orphan*/  state; int /*<<< orphan*/  queue; } ;
struct saa7146_buf {TYPE_1__ vb; int /*<<< orphan*/  (* activate ) (struct saa7146_dev*,struct saa7146_buf*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DEB_D (char*,struct saa7146_buf*) ; 
 int /*<<< orphan*/  DEB_EE (char*,struct saa7146_dev*,struct saa7146_dmaqueue*,struct saa7146_buf*) ; 
 int /*<<< orphan*/  VIDEOBUF_QUEUED ; 
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct saa7146_dev*,struct saa7146_buf*,int /*<<< orphan*/ *) ; 

int saa7146_buffer_queue(struct saa7146_dev *dev,
			 struct saa7146_dmaqueue *q,
			 struct saa7146_buf *buf)
{
	assert_spin_locked(&dev->slock);
	DEB_EE("dev:%p, dmaq:%p, buf:%p\n", dev, q, buf);

	BUG_ON(!q);

	if (NULL == q->curr) {
		q->curr = buf;
		DEB_D("immediately activating buffer %p\n", buf);
		buf->activate(dev,buf,NULL);
	} else {
		list_add_tail(&buf->vb.queue,&q->queue);
		buf->vb.state = VIDEOBUF_QUEUED;
		DEB_D("adding buffer %p to queue. (active buffer present)\n",
		      buf);
	}
	return 0;
}