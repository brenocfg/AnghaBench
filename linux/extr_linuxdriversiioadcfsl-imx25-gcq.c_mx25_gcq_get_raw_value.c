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
struct mx25_gcq_priv {int /*<<< orphan*/  regs; int /*<<< orphan*/  completed; } ;
struct iio_chan_spec {int /*<<< orphan*/  channel; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int IIO_VAL_INT ; 
 int /*<<< orphan*/  MX25_ADCQ_CR ; 
 int /*<<< orphan*/  MX25_ADCQ_CR_FQS ; 
 int /*<<< orphan*/  MX25_ADCQ_FIFO ; 
 int MX25_ADCQ_FIFO_DATA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MX25_ADCQ_ITEM (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MX25_ADCQ_ITEM_7_0 ; 
 int /*<<< orphan*/  MX25_ADCQ_MR ; 
 int /*<<< orphan*/  MX25_ADCQ_MR_EOQ_IRQ ; 
 int /*<<< orphan*/  MX25_GCQ_TIMEOUT ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 long wait_for_completion_interruptible_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mx25_gcq_get_raw_value(struct device *dev,
				  struct iio_chan_spec const *chan,
				  struct mx25_gcq_priv *priv,
				  int *val)
{
	long timeout;
	u32 data;

	/* Setup the configuration we want to use */
	regmap_write(priv->regs, MX25_ADCQ_ITEM_7_0,
		     MX25_ADCQ_ITEM(0, chan->channel));

	regmap_update_bits(priv->regs, MX25_ADCQ_MR, MX25_ADCQ_MR_EOQ_IRQ, 0);

	/* Trigger queue for one run */
	regmap_update_bits(priv->regs, MX25_ADCQ_CR, MX25_ADCQ_CR_FQS,
			   MX25_ADCQ_CR_FQS);

	timeout = wait_for_completion_interruptible_timeout(
		&priv->completed, MX25_GCQ_TIMEOUT);
	if (timeout < 0) {
		dev_err(dev, "ADC wait for measurement failed\n");
		return timeout;
	} else if (timeout == 0) {
		dev_err(dev, "ADC timed out\n");
		return -ETIMEDOUT;
	}

	regmap_read(priv->regs, MX25_ADCQ_FIFO, &data);

	*val = MX25_ADCQ_FIFO_DATA(data);

	return IIO_VAL_INT;
}