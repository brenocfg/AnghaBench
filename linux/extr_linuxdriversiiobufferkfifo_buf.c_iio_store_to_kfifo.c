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
struct iio_kfifo {int /*<<< orphan*/  kf; } ;
struct iio_buffer {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 struct iio_kfifo* iio_to_kfifo (struct iio_buffer*) ; 
 int kfifo_in (int /*<<< orphan*/ *,void const*,int) ; 

__attribute__((used)) static int iio_store_to_kfifo(struct iio_buffer *r,
			      const void *data)
{
	int ret;
	struct iio_kfifo *kf = iio_to_kfifo(r);
	ret = kfifo_in(&kf->kf, data, 1);
	if (ret != 1)
		return -EBUSY;
	return 0;
}