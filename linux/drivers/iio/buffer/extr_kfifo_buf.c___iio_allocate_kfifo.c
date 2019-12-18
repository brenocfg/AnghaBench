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
struct __kfifo {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t UINT_MAX ; 
 int __kfifo_alloc (struct __kfifo*,unsigned int,size_t,int /*<<< orphan*/ ) ; 
 size_t roundup_pow_of_two (unsigned int) ; 

__attribute__((used)) static inline int __iio_allocate_kfifo(struct iio_kfifo *buf,
			size_t bytes_per_datum, unsigned int length)
{
	if ((length == 0) || (bytes_per_datum == 0))
		return -EINVAL;

	/*
	 * Make sure we don't overflow an unsigned int after kfifo rounds up to
	 * the next power of 2.
	 */
	if (roundup_pow_of_two(length) > UINT_MAX / bytes_per_datum)
		return -EINVAL;

	return __kfifo_alloc((struct __kfifo *)&buf->kf, length,
			     bytes_per_datum, GFP_KERNEL);
}