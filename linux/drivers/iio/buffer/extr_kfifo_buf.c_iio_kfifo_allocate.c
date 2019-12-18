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
struct iio_buffer {int length; int /*<<< orphan*/ * access; } ;
struct iio_kfifo {int update_needed; struct iio_buffer buffer; int /*<<< orphan*/  user_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  iio_buffer_init (struct iio_buffer*) ; 
 int /*<<< orphan*/  kfifo_access_funcs ; 
 struct iio_kfifo* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

struct iio_buffer *iio_kfifo_allocate(void)
{
	struct iio_kfifo *kf;

	kf = kzalloc(sizeof(*kf), GFP_KERNEL);
	if (!kf)
		return NULL;

	kf->update_needed = true;
	iio_buffer_init(&kf->buffer);
	kf->buffer.access = &kfifo_access_funcs;
	kf->buffer.length = 2;
	mutex_init(&kf->user_lock);

	return &kf->buffer;
}