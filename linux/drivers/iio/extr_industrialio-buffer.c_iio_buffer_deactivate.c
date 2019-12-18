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
struct iio_buffer {int /*<<< orphan*/  pollq; int /*<<< orphan*/  buffer_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  iio_buffer_put (struct iio_buffer*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iio_buffer_deactivate(struct iio_buffer *buffer)
{
	list_del_init(&buffer->buffer_list);
	wake_up_interruptible(&buffer->pollq);
	iio_buffer_put(buffer);
}