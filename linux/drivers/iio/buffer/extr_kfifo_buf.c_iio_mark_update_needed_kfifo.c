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
struct iio_kfifo {int update_needed; } ;
struct iio_buffer {int dummy; } ;

/* Variables and functions */
 struct iio_kfifo* iio_to_kfifo (struct iio_buffer*) ; 

__attribute__((used)) static int iio_mark_update_needed_kfifo(struct iio_buffer *r)
{
	struct iio_kfifo *kf = iio_to_kfifo(r);
	kf->update_needed = true;
	return 0;
}