#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct iio_dev {TYPE_3__* buffer; } ;
struct TYPE_5__ {int /*<<< orphan*/  attrs; } ;
struct TYPE_4__ {int /*<<< orphan*/  attrs; } ;
struct TYPE_6__ {int /*<<< orphan*/  scan_el_dev_attr_list; TYPE_2__ scan_el_group; TYPE_1__ buffer_group; int /*<<< orphan*/  scan_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  bitmap_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_free_chan_devattr_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

void iio_buffer_free_sysfs_and_mask(struct iio_dev *indio_dev)
{
	if (!indio_dev->buffer)
		return;

	bitmap_free(indio_dev->buffer->scan_mask);
	kfree(indio_dev->buffer->buffer_group.attrs);
	kfree(indio_dev->buffer->scan_el_group.attrs);
	iio_free_chan_devattr_list(&indio_dev->buffer->scan_el_dev_attr_list);
}