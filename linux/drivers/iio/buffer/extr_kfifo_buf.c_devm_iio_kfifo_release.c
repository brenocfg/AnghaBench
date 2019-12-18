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
struct iio_buffer {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  iio_kfifo_free (struct iio_buffer*) ; 

__attribute__((used)) static void devm_iio_kfifo_release(struct device *dev, void *res)
{
	iio_kfifo_free(*(struct iio_buffer **)res);
}