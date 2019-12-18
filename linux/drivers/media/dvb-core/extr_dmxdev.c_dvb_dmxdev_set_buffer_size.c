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
struct dvb_ringbuffer {unsigned long size; void* data; } ;
struct dmxdev_filter {scalar_t__ state; TYPE_1__* dev; struct dvb_ringbuffer buffer; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ DMXDEV_STATE_GO ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  dvb_ringbuffer_reset (struct dvb_ringbuffer*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfree (void*) ; 
 void* vmalloc (unsigned long) ; 

__attribute__((used)) static int dvb_dmxdev_set_buffer_size(struct dmxdev_filter *dmxdevfilter,
				      unsigned long size)
{
	struct dvb_ringbuffer *buf = &dmxdevfilter->buffer;
	void *newmem;
	void *oldmem;

	if (buf->size == size)
		return 0;
	if (!size)
		return -EINVAL;
	if (dmxdevfilter->state >= DMXDEV_STATE_GO)
		return -EBUSY;

	newmem = vmalloc(size);
	if (!newmem)
		return -ENOMEM;

	oldmem = buf->data;

	spin_lock_irq(&dmxdevfilter->dev->lock);
	buf->data = newmem;
	buf->size = size;

	/* reset and not flush in case the buffer shrinks */
	dvb_ringbuffer_reset(buf);
	spin_unlock_irq(&dmxdevfilter->dev->lock);

	vfree(oldmem);

	return 0;
}