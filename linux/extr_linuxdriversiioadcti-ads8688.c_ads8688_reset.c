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
typedef  int /*<<< orphan*/  u32 ;
struct iio_dev {int dummy; } ;
struct ads8688_state {TYPE_1__* data; int /*<<< orphan*/  spi; } ;
struct TYPE_2__ {int /*<<< orphan*/ * d8; int /*<<< orphan*/  d32; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADS8688_CMD_DONT_CARE_BITS ; 
 int /*<<< orphan*/  ADS8688_CMD_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ADS8688_CMD_REG_RST ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 struct ads8688_state* iio_priv (struct iio_dev*) ; 
 int spi_write (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ads8688_reset(struct iio_dev *indio_dev)
{
	struct ads8688_state *st = iio_priv(indio_dev);
	u32 tmp;

	tmp = ADS8688_CMD_REG(ADS8688_CMD_REG_RST);
	tmp <<= ADS8688_CMD_DONT_CARE_BITS;
	st->data[0].d32 = cpu_to_be32(tmp);

	return spi_write(st->spi, &st->data[0].d8[0], 4);
}