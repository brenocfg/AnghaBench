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
struct nau7802_state {int last_value; TYPE_1__* client; int /*<<< orphan*/  value_ok; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int IIO_VAL_INT ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 struct nau7802_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int nau7802_read_conversion (struct nau7802_state*) ; 
 int /*<<< orphan*/  nau7802_sync (struct nau7802_state*) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int wait_for_completion_interruptible_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nau7802_read_irq(struct iio_dev *indio_dev,
			struct iio_chan_spec const *chan,
			int *val)
{
	struct nau7802_state *st = iio_priv(indio_dev);
	int ret;

	reinit_completion(&st->value_ok);
	enable_irq(st->client->irq);

	nau7802_sync(st);

	/* read registers to ensure we flush everything */
	ret = nau7802_read_conversion(st);
	if (ret < 0)
		goto read_chan_info_failure;

	/* Wait for a conversion to finish */
	ret = wait_for_completion_interruptible_timeout(&st->value_ok,
			msecs_to_jiffies(1000));
	if (ret == 0)
		ret = -ETIMEDOUT;

	if (ret < 0)
		goto read_chan_info_failure;

	disable_irq(st->client->irq);

	*val = st->last_value;

	return IIO_VAL_INT;

read_chan_info_failure:
	disable_irq(st->client->irq);

	return ret;
}