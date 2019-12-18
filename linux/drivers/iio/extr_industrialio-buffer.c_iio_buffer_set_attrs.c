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
struct iio_buffer {struct attribute const** attrs; } ;
struct attribute {int dummy; } ;

/* Variables and functions */

void iio_buffer_set_attrs(struct iio_buffer *buffer,
			 const struct attribute **attrs)
{
	buffer->attrs = attrs;
}