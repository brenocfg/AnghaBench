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
struct saa7146_dmaqueue {int /*<<< orphan*/ * curr; } ;
struct saa7146_vv {struct saa7146_dmaqueue video_dmaq; } ;
struct saa7146_dev {int /*<<< orphan*/  slock; struct saa7146_vv* vv_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEB_CAP (char*) ; 
 int /*<<< orphan*/  VIDEOBUF_DONE ; 
 int /*<<< orphan*/  saa7146_buffer_finish (struct saa7146_dev*,struct saa7146_dmaqueue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saa7146_buffer_next (struct saa7146_dev*,struct saa7146_dmaqueue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void video_irq_done(struct saa7146_dev *dev, unsigned long st)
{
	struct saa7146_vv *vv = dev->vv_data;
	struct saa7146_dmaqueue *q = &vv->video_dmaq;

	spin_lock(&dev->slock);
	DEB_CAP("called\n");

	/* only finish the buffer if we have one... */
	if( NULL != q->curr ) {
		saa7146_buffer_finish(dev,q,VIDEOBUF_DONE);
	}
	saa7146_buffer_next(dev,q,0);

	spin_unlock(&dev->slock);
}