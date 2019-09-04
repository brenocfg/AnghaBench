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
struct iio_dev {int /*<<< orphan*/  mlock; } ;
struct ad5449 {int /*<<< orphan*/ * data; int /*<<< orphan*/  spi; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_be16 (unsigned int) ; 
 struct ad5449* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int spi_write (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ad5449_write(struct iio_dev *indio_dev, unsigned int addr,
	unsigned int val)
{
	struct ad5449 *st = iio_priv(indio_dev);
	int ret;

	mutex_lock(&indio_dev->mlock);
	st->data[0] = cpu_to_be16((addr << 12) | val);
	ret = spi_write(st->spi, st->data, 2);
	mutex_unlock(&indio_dev->mlock);

	return ret;
}