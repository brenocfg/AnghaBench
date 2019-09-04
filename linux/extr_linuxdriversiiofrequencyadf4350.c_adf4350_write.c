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
typedef  int /*<<< orphan*/  u32 ;
struct iio_dev {int /*<<< orphan*/  mlock; } ;
struct iio_chan_spec {int dummy; } ;
struct adf4350_state {unsigned long long clkin; unsigned long long freq_req; unsigned long long chspc; int /*<<< orphan*/ * regs; int /*<<< orphan*/  clk; } ;
typedef  int ssize_t ;

/* Variables and functions */
#define  ADF4350_FREQ 131 
#define  ADF4350_FREQ_REFIN 130 
#define  ADF4350_FREQ_RESOLUTION 129 
 unsigned long long ADF4350_MAX_FREQ_REFIN ; 
#define  ADF4350_PWRDOWN 128 
 size_t ADF4350_REG2 ; 
 int /*<<< orphan*/  ADF4350_REG2_POWER_DOWN_EN ; 
 int EINVAL ; 
 int adf4350_set_freq (struct adf4350_state*,unsigned long long) ; 
 int /*<<< orphan*/  adf4350_sync_config (struct adf4350_state*) ; 
 unsigned long clk_round_rate (int /*<<< orphan*/ ,unsigned long long) ; 
 int clk_set_rate (int /*<<< orphan*/ ,unsigned long) ; 
 struct adf4350_state* iio_priv (struct iio_dev*) ; 
 int kstrtoull (char const*,int,unsigned long long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t adf4350_write(struct iio_dev *indio_dev,
				    uintptr_t private,
				    const struct iio_chan_spec *chan,
				    const char *buf, size_t len)
{
	struct adf4350_state *st = iio_priv(indio_dev);
	unsigned long long readin;
	unsigned long tmp;
	int ret;

	ret = kstrtoull(buf, 10, &readin);
	if (ret)
		return ret;

	mutex_lock(&indio_dev->mlock);
	switch ((u32)private) {
	case ADF4350_FREQ:
		ret = adf4350_set_freq(st, readin);
		break;
	case ADF4350_FREQ_REFIN:
		if (readin > ADF4350_MAX_FREQ_REFIN) {
			ret = -EINVAL;
			break;
		}

		if (st->clk) {
			tmp = clk_round_rate(st->clk, readin);
			if (tmp != readin) {
				ret = -EINVAL;
				break;
			}
			ret = clk_set_rate(st->clk, tmp);
			if (ret < 0)
				break;
		}
		st->clkin = readin;
		ret = adf4350_set_freq(st, st->freq_req);
		break;
	case ADF4350_FREQ_RESOLUTION:
		if (readin == 0)
			ret = -EINVAL;
		else
			st->chspc = readin;
		break;
	case ADF4350_PWRDOWN:
		if (readin)
			st->regs[ADF4350_REG2] |= ADF4350_REG2_POWER_DOWN_EN;
		else
			st->regs[ADF4350_REG2] &= ~ADF4350_REG2_POWER_DOWN_EN;

		adf4350_sync_config(st);
		break;
	default:
		ret = -EINVAL;
	}
	mutex_unlock(&indio_dev->mlock);

	return ret ? ret : len;
}