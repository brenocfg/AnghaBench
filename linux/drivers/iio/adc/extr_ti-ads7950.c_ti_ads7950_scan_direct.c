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
struct ti_ads7950_state {int single_tx; int single_rx; int /*<<< orphan*/  slock; int /*<<< orphan*/  scan_single_msg; int /*<<< orphan*/  spi; } ;
struct iio_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TI_ADS7950_CR_CHAN (unsigned int) ; 
 int TI_ADS7950_MAN_CMD (int /*<<< orphan*/ ) ; 
 struct ti_ads7950_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int spi_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ti_ads7950_scan_direct(struct iio_dev *indio_dev, unsigned int ch)
{
	struct ti_ads7950_state *st = iio_priv(indio_dev);
	int ret, cmd;

	mutex_lock(&st->slock);
	cmd = TI_ADS7950_MAN_CMD(TI_ADS7950_CR_CHAN(ch));
	st->single_tx = cmd;

	ret = spi_sync(st->spi, &st->scan_single_msg);
	if (ret)
		goto out;

	ret = st->single_rx;

out:
	mutex_unlock(&st->slock);

	return ret;
}