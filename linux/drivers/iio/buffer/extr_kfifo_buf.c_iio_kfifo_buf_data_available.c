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
struct iio_kfifo {int /*<<< orphan*/  user_lock; int /*<<< orphan*/  kf; } ;
struct iio_buffer {int dummy; } ;

/* Variables and functions */
 struct iio_kfifo* iio_to_kfifo (struct iio_buffer*) ; 
 size_t kfifo_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static size_t iio_kfifo_buf_data_available(struct iio_buffer *r)
{
	struct iio_kfifo *kf = iio_to_kfifo(r);
	size_t samples;

	mutex_lock(&kf->user_lock);
	samples = kfifo_len(&kf->kf);
	mutex_unlock(&kf->user_lock);

	return samples;
}