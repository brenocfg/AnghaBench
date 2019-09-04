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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct iio_dev {int /*<<< orphan*/  mlock; } ;
struct ad5761_state {int dummy; } ;

/* Variables and functions */
 int _ad5761_spi_read (struct ad5761_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct ad5761_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ad5761_spi_read(struct iio_dev *indio_dev, u8 addr, u16 *val)
{
	struct ad5761_state *st = iio_priv(indio_dev);
	int ret;

	mutex_lock(&indio_dev->mlock);
	ret = _ad5761_spi_read(st, addr, val);
	mutex_unlock(&indio_dev->mlock);

	return ret;
}