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
struct comedi_subdevice {int index; int minor; int /*<<< orphan*/  spin_lock; int /*<<< orphan*/  async_dma_dir; struct comedi_device* device; } ;
struct comedi_device {int n_subdevices; struct comedi_subdevice* subdevices; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_NONE ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct comedi_subdevice* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int comedi_alloc_subdevices(struct comedi_device *dev, int num_subdevices)
{
	struct comedi_subdevice *s;
	int i;

	if (num_subdevices < 1)
		return -EINVAL;

	s = kcalloc(num_subdevices, sizeof(*s), GFP_KERNEL);
	if (!s)
		return -ENOMEM;
	dev->subdevices = s;
	dev->n_subdevices = num_subdevices;

	for (i = 0; i < num_subdevices; ++i) {
		s = &dev->subdevices[i];
		s->device = dev;
		s->index = i;
		s->async_dma_dir = DMA_NONE;
		spin_lock_init(&s->spin_lock);
		s->minor = -1;
	}
	return 0;
}