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
struct iio_buffer {int /*<<< orphan*/  ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  iio_buffer_release ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void iio_buffer_put(struct iio_buffer *buffer)
{
	if (buffer)
		kref_put(&buffer->ref, iio_buffer_release);
}