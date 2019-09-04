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
struct spi_device {int dummy; } ;
struct regulator {int dummy; } ;
struct iio_dev {int dummy; } ;
struct adf4350_state {scalar_t__ clk; int /*<<< orphan*/ * regs; struct regulator* reg; } ;

/* Variables and functions */
 size_t ADF4350_REG2 ; 
 int /*<<< orphan*/  ADF4350_REG2_POWER_DOWN_EN ; 
 int /*<<< orphan*/  IS_ERR (struct regulator*) ; 
 int /*<<< orphan*/  adf4350_sync_config (struct adf4350_state*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (scalar_t__) ; 
 int /*<<< orphan*/  iio_device_unregister (struct iio_dev*) ; 
 struct adf4350_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  regulator_disable (struct regulator*) ; 
 struct iio_dev* spi_get_drvdata (struct spi_device*) ; 

__attribute__((used)) static int adf4350_remove(struct spi_device *spi)
{
	struct iio_dev *indio_dev = spi_get_drvdata(spi);
	struct adf4350_state *st = iio_priv(indio_dev);
	struct regulator *reg = st->reg;

	st->regs[ADF4350_REG2] |= ADF4350_REG2_POWER_DOWN_EN;
	adf4350_sync_config(st);

	iio_device_unregister(indio_dev);

	if (st->clk)
		clk_disable_unprepare(st->clk);

	if (!IS_ERR(reg))
		regulator_disable(reg);

	return 0;
}