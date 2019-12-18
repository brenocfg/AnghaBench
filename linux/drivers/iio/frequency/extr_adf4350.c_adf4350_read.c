#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long long u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct iio_dev {int /*<<< orphan*/  mlock; } ;
struct iio_chan_spec {int dummy; } ;
struct adf4350_state {int r0_int; int r1_mod; int r0_fract; int r4_rf_div_sel; unsigned long long clkin; unsigned long long chspc; int* regs; int /*<<< orphan*/  clk; TYPE_2__* spi; TYPE_1__* pdata; int /*<<< orphan*/  fpfd; } ;
typedef  int ssize_t ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  gpio_lock_detect; } ;

/* Variables and functions */
#define  ADF4350_FREQ 131 
#define  ADF4350_FREQ_REFIN 130 
#define  ADF4350_FREQ_RESOLUTION 129 
#define  ADF4350_PWRDOWN 128 
 size_t ADF4350_REG2 ; 
 int ADF4350_REG2_POWER_DOWN_EN ; 
 int EBUSY ; 
 int EINVAL ; 
 unsigned long long clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  do_div (unsigned long long,int) ; 
 int /*<<< orphan*/  gpio_get_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_is_valid (int /*<<< orphan*/ ) ; 
 struct adf4350_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sprintf (char*,char*,unsigned long long) ; 

__attribute__((used)) static ssize_t adf4350_read(struct iio_dev *indio_dev,
				   uintptr_t private,
				   const struct iio_chan_spec *chan,
				   char *buf)
{
	struct adf4350_state *st = iio_priv(indio_dev);
	unsigned long long val;
	int ret = 0;

	mutex_lock(&indio_dev->mlock);
	switch ((u32)private) {
	case ADF4350_FREQ:
		val = (u64)((st->r0_int * st->r1_mod) + st->r0_fract) *
			(u64)st->fpfd;
		do_div(val, st->r1_mod * (1 << st->r4_rf_div_sel));
		/* PLL unlocked? return error */
		if (gpio_is_valid(st->pdata->gpio_lock_detect))
			if (!gpio_get_value(st->pdata->gpio_lock_detect)) {
				dev_dbg(&st->spi->dev, "PLL un-locked\n");
				ret = -EBUSY;
			}
		break;
	case ADF4350_FREQ_REFIN:
		if (st->clk)
			st->clkin = clk_get_rate(st->clk);

		val = st->clkin;
		break;
	case ADF4350_FREQ_RESOLUTION:
		val = st->chspc;
		break;
	case ADF4350_PWRDOWN:
		val = !!(st->regs[ADF4350_REG2] & ADF4350_REG2_POWER_DOWN_EN);
		break;
	default:
		ret = -EINVAL;
		val = 0;
	}
	mutex_unlock(&indio_dev->mlock);

	return ret < 0 ? ret : sprintf(buf, "%llu\n", val);
}