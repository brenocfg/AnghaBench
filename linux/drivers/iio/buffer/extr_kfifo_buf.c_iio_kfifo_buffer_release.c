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
struct iio_kfifo {int /*<<< orphan*/  kf; int /*<<< orphan*/  user_lock; } ;
struct iio_buffer {int dummy; } ;

/* Variables and functions */
 struct iio_kfifo* iio_to_kfifo (struct iio_buffer*) ; 
 int /*<<< orphan*/  kfifo_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct iio_kfifo*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iio_kfifo_buffer_release(struct iio_buffer *buffer)
{
	struct iio_kfifo *kf = iio_to_kfifo(buffer);

	mutex_destroy(&kf->user_lock);
	kfifo_free(&kf->kf);
	kfree(kf);
}