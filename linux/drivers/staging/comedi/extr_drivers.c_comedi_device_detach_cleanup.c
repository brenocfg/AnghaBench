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
struct comedi_subdevice {struct comedi_subdevice* readback; struct comedi_subdevice* async; struct comedi_subdevice* private; } ;
struct comedi_device {int n_subdevices; int ioenabled; int /*<<< orphan*/ * close; int /*<<< orphan*/ * open; int /*<<< orphan*/ * write_subdev; int /*<<< orphan*/ * read_subdev; scalar_t__ irq; scalar_t__ iolen; scalar_t__ iobase; int /*<<< orphan*/ * mmio; int /*<<< orphan*/ * board_ptr; int /*<<< orphan*/ * board_name; int /*<<< orphan*/ * driver; struct comedi_subdevice* pacer; struct comedi_subdevice* private; struct comedi_subdevice* subdevices; int /*<<< orphan*/  mutex; int /*<<< orphan*/  attach_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  comedi_buf_alloc (struct comedi_device*,struct comedi_subdevice*,int /*<<< orphan*/ ) ; 
 scalar_t__ comedi_can_auto_free_spriv (struct comedi_subdevice*) ; 
 int /*<<< orphan*/  comedi_clear_hw_dev (struct comedi_device*) ; 
 int /*<<< orphan*/  comedi_free_subdevice_minor (struct comedi_subdevice*) ; 
 int /*<<< orphan*/  kfree (struct comedi_subdevice*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void comedi_device_detach_cleanup(struct comedi_device *dev)
{
	int i;
	struct comedi_subdevice *s;

	lockdep_assert_held(&dev->attach_lock);
	lockdep_assert_held(&dev->mutex);
	if (dev->subdevices) {
		for (i = 0; i < dev->n_subdevices; i++) {
			s = &dev->subdevices[i];
			if (comedi_can_auto_free_spriv(s))
				kfree(s->private);
			comedi_free_subdevice_minor(s);
			if (s->async) {
				comedi_buf_alloc(dev, s, 0);
				kfree(s->async);
			}
			kfree(s->readback);
		}
		kfree(dev->subdevices);
		dev->subdevices = NULL;
		dev->n_subdevices = 0;
	}
	kfree(dev->private);
	kfree(dev->pacer);
	dev->private = NULL;
	dev->pacer = NULL;
	dev->driver = NULL;
	dev->board_name = NULL;
	dev->board_ptr = NULL;
	dev->mmio = NULL;
	dev->iobase = 0;
	dev->iolen = 0;
	dev->ioenabled = false;
	dev->irq = 0;
	dev->read_subdev = NULL;
	dev->write_subdev = NULL;
	dev->open = NULL;
	dev->close = NULL;
	comedi_clear_hw_dev(dev);
}