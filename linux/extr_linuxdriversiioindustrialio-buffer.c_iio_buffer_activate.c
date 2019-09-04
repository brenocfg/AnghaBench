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
struct iio_dev {int /*<<< orphan*/  buffer_list; } ;
struct iio_buffer {int /*<<< orphan*/  buffer_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  iio_buffer_get (struct iio_buffer*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iio_buffer_activate(struct iio_dev *indio_dev,
	struct iio_buffer *buffer)
{
	iio_buffer_get(buffer);
	list_add(&buffer->buffer_list, &indio_dev->buffer_list);
}