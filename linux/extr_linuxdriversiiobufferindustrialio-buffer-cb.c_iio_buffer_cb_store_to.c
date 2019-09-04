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
struct iio_cb_buffer {int (* cb ) (void const*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  private; } ;
struct iio_buffer {int dummy; } ;

/* Variables and functions */
 struct iio_cb_buffer* buffer_to_cb_buffer (struct iio_buffer*) ; 
 int stub1 (void const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iio_buffer_cb_store_to(struct iio_buffer *buffer, const void *data)
{
	struct iio_cb_buffer *cb_buff = buffer_to_cb_buffer(buffer);
	return cb_buff->cb(data, cb_buff->private);
}