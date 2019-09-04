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
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_iio_kfifo_match ; 
 int /*<<< orphan*/  devm_iio_kfifo_release ; 
 int /*<<< orphan*/  devres_release (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct iio_buffer*) ; 

void devm_iio_kfifo_free(struct device *dev, struct iio_buffer *r)
{
	WARN_ON(devres_release(dev, devm_iio_kfifo_release,
			       devm_iio_kfifo_match, r));
}