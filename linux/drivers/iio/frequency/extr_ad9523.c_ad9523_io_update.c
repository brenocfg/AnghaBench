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
struct iio_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AD9523_IO_UPDATE ; 
 int /*<<< orphan*/  AD9523_IO_UPDATE_EN ; 
 int ad9523_write (struct iio_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ad9523_io_update(struct iio_dev *indio_dev)
{
	return ad9523_write(indio_dev, AD9523_IO_UPDATE, AD9523_IO_UPDATE_EN);
}