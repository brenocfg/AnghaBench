#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct iio_dev {int dummy; } ;
struct ad5421_state {TYPE_1__* data; int /*<<< orphan*/  spi; } ;
struct TYPE_2__ {int /*<<< orphan*/ * d8; int /*<<< orphan*/  d32; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_be32 (unsigned int) ; 
 struct ad5421_state* iio_priv (struct iio_dev*) ; 
 int spi_write (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ad5421_write_unlocked(struct iio_dev *indio_dev,
	unsigned int reg, unsigned int val)
{
	struct ad5421_state *st = iio_priv(indio_dev);

	st->data[0].d32 = cpu_to_be32((reg << 16) | val);

	return spi_write(st->spi, &st->data[0].d8[1], 3);
}