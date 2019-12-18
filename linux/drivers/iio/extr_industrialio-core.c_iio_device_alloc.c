#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * bus; int /*<<< orphan*/ * type; int /*<<< orphan*/  groups; } ;
struct iio_dev {scalar_t__ id; int /*<<< orphan*/  buffer_list; TYPE_1__ dev; int /*<<< orphan*/  channel_attr_list; int /*<<< orphan*/  info_exist_lock; int /*<<< orphan*/  mlock; int /*<<< orphan*/  groups; } ;

/* Variables and functions */
 size_t ALIGN (size_t,int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IIO_ALIGN ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_1__*,void*) ; 
 int /*<<< orphan*/  dev_set_name (TYPE_1__*,char*,scalar_t__) ; 
 int /*<<< orphan*/  device_initialize (TYPE_1__*) ; 
 scalar_t__ ida_simple_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_bus_type ; 
 int /*<<< orphan*/  iio_device_type ; 
 int /*<<< orphan*/  iio_ida ; 
 int /*<<< orphan*/  kfree (struct iio_dev*) ; 
 struct iio_dev* kzalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

struct iio_dev *iio_device_alloc(int sizeof_priv)
{
	struct iio_dev *dev;
	size_t alloc_size;

	alloc_size = sizeof(struct iio_dev);
	if (sizeof_priv) {
		alloc_size = ALIGN(alloc_size, IIO_ALIGN);
		alloc_size += sizeof_priv;
	}
	/* ensure 32-byte alignment of whole construct ? */
	alloc_size += IIO_ALIGN - 1;

	dev = kzalloc(alloc_size, GFP_KERNEL);

	if (dev) {
		dev->dev.groups = dev->groups;
		dev->dev.type = &iio_device_type;
		dev->dev.bus = &iio_bus_type;
		device_initialize(&dev->dev);
		dev_set_drvdata(&dev->dev, (void *)dev);
		mutex_init(&dev->mlock);
		mutex_init(&dev->info_exist_lock);
		INIT_LIST_HEAD(&dev->channel_attr_list);

		dev->id = ida_simple_get(&iio_ida, 0, 0, GFP_KERNEL);
		if (dev->id < 0) {
			/* cannot use a dev_err as the name isn't available */
			pr_err("failed to get device id\n");
			kfree(dev);
			return NULL;
		}
		dev_set_name(&dev->dev, "iio:device%d", dev->id);
		INIT_LIST_HEAD(&dev->buffer_list);
	}

	return dev;
}