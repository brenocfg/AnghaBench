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
struct iio_buffer {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  devm_iio_kfifo_release ; 
 int /*<<< orphan*/  devres_add (struct device*,struct iio_buffer**) ; 
 struct iio_buffer** devres_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_free (struct iio_buffer**) ; 
 struct iio_buffer* iio_kfifo_allocate () ; 

struct iio_buffer *devm_iio_kfifo_allocate(struct device *dev)
{
	struct iio_buffer **ptr, *r;

	ptr = devres_alloc(devm_iio_kfifo_release, sizeof(*ptr), GFP_KERNEL);
	if (!ptr)
		return NULL;

	r = iio_kfifo_allocate();
	if (r) {
		*ptr = r;
		devres_add(dev, ptr);
	} else {
		devres_free(ptr);
	}

	return r;
}