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
typedef  int u32 ;
typedef  int u16 ;
struct iproc_adc_priv {int chan_val; int chan_id; int /*<<< orphan*/  mutex; int /*<<< orphan*/  regmap; int /*<<< orphan*/  completion; } ;
struct iio_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BIT (int) ; 
 int EIO ; 
 int ETIMEDOUT ; 
 int IPROC_ADC_AUXDATA_RDY_INTR ; 
 int IPROC_ADC_CHANNEL_ENABLE ; 
 int IPROC_ADC_CHANNEL_ENABLE_MASK ; 
 scalar_t__ IPROC_ADC_CHANNEL_INTERRUPT_MASK ; 
 int IPROC_ADC_CHANNEL_MODE ; 
 int IPROC_ADC_CHANNEL_MODE_MASK ; 
 int IPROC_ADC_CHANNEL_MODE_SNAPSHOT ; 
 int IPROC_ADC_CHANNEL_OFFSET ; 
 scalar_t__ IPROC_ADC_CHANNEL_REGCTL1 ; 
 scalar_t__ IPROC_ADC_CHANNEL_REGCTL2 ; 
 int IPROC_ADC_CHANNEL_ROUNDS ; 
 int IPROC_ADC_CHANNEL_ROUNDS_MASK ; 
 int IPROC_ADC_CHANNEL_WATERMARK_MASK ; 
 int IPROC_ADC_CHANNEL_WTRMRK_INTR_MASK ; 
 int IPROC_ADC_INTMASK_RETRY_ATTEMPTS ; 
 int IPROC_ADC_INTR ; 
 int IPROC_ADC_INTR_MASK ; 
 int /*<<< orphan*/  IPROC_ADC_READ_TIMEOUT ; 
 int IPROC_ADC_WATER_MARK_INTR_ENABLE ; 
 scalar_t__ IPROC_INTERRUPT_MASK ; 
 scalar_t__ IPROC_INTERRUPT_STATUS ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct iproc_adc_priv* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iproc_adc_reg_dump (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,scalar_t__,int*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,scalar_t__,int,int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 
 scalar_t__ wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iproc_adc_do_read(struct iio_dev *indio_dev,
			   int channel,
			   u16 *p_adc_data)
{
	int read_len = 0;
	u32 val;
	u32 mask;
	u32 val_check;
	int failed_cnt = 0;
	struct iproc_adc_priv *adc_priv = iio_priv(indio_dev);

	mutex_lock(&adc_priv->mutex);

	/*
	 * After a read is complete the ADC interrupts will be disabled so
	 * we can assume this section of code is safe from interrupts.
	 */
	adc_priv->chan_val = -1;
	adc_priv->chan_id = channel;

	reinit_completion(&adc_priv->completion);
	/* Clear any pending interrupt */
	regmap_update_bits(adc_priv->regmap, IPROC_INTERRUPT_STATUS,
			IPROC_ADC_INTR_MASK | IPROC_ADC_AUXDATA_RDY_INTR,
			((0x0 << channel) << IPROC_ADC_INTR) |
			IPROC_ADC_AUXDATA_RDY_INTR);

	/* Configure channel for snapshot mode and enable  */
	val = (BIT(IPROC_ADC_CHANNEL_ROUNDS) |
		(IPROC_ADC_CHANNEL_MODE_SNAPSHOT << IPROC_ADC_CHANNEL_MODE) |
		(0x1 << IPROC_ADC_CHANNEL_ENABLE));

	mask = IPROC_ADC_CHANNEL_ROUNDS_MASK | IPROC_ADC_CHANNEL_MODE_MASK |
		IPROC_ADC_CHANNEL_ENABLE_MASK;
	regmap_update_bits(adc_priv->regmap, (IPROC_ADC_CHANNEL_REGCTL1 +
				IPROC_ADC_CHANNEL_OFFSET * channel),
				mask, val);

	/* Set the Watermark for a channel */
	regmap_update_bits(adc_priv->regmap, (IPROC_ADC_CHANNEL_REGCTL2 +
					IPROC_ADC_CHANNEL_OFFSET * channel),
					IPROC_ADC_CHANNEL_WATERMARK_MASK,
					0x1);

	/* Enable water mark interrupt */
	regmap_update_bits(adc_priv->regmap, (IPROC_ADC_CHANNEL_INTERRUPT_MASK +
					IPROC_ADC_CHANNEL_OFFSET *
					channel),
					IPROC_ADC_CHANNEL_WTRMRK_INTR_MASK,
					IPROC_ADC_WATER_MARK_INTR_ENABLE);
	regmap_read(adc_priv->regmap, IPROC_INTERRUPT_MASK, &val);

	/* Enable ADC interrupt for a channel */
	val |= (BIT(channel) << IPROC_ADC_INTR);
	regmap_write(adc_priv->regmap, IPROC_INTERRUPT_MASK, val);

	/*
	 * There seems to be a very rare issue where writing to this register
	 * does not take effect.  To work around the issue we will try multiple
	 * writes.  In total we will spend about 10*10 = 100 us attempting this.
	 * Testing has shown that this may loop a few time, but we have never
	 * hit the full count.
	 */
	regmap_read(adc_priv->regmap, IPROC_INTERRUPT_MASK, &val_check);
	while (val_check != val) {
		failed_cnt++;

		if (failed_cnt > IPROC_ADC_INTMASK_RETRY_ATTEMPTS)
			break;

		udelay(10);
		regmap_update_bits(adc_priv->regmap, IPROC_INTERRUPT_MASK,
				IPROC_ADC_INTR_MASK,
				((0x1 << channel) <<
				IPROC_ADC_INTR));

		regmap_read(adc_priv->regmap, IPROC_INTERRUPT_MASK, &val_check);
	}

	if (failed_cnt) {
		dev_dbg(&indio_dev->dev,
			"IntMask failed (%d times)", failed_cnt);
		if (failed_cnt > IPROC_ADC_INTMASK_RETRY_ATTEMPTS) {
			dev_err(&indio_dev->dev,
				"IntMask set failed. Read will likely fail.");
			read_len = -EIO;
			goto adc_err;
		};
	}
	regmap_read(adc_priv->regmap, IPROC_INTERRUPT_MASK, &val_check);

	if (wait_for_completion_timeout(&adc_priv->completion,
		IPROC_ADC_READ_TIMEOUT) > 0) {

		/* Only the lower 16 bits are relevant */
		*p_adc_data = adc_priv->chan_val & 0xFFFF;
		read_len = sizeof(*p_adc_data);

	} else {
		/*
		 * We never got the interrupt, something went wrong.
		 * Perhaps the interrupt may still be coming, we do not want
		 * that now.  Lets disable the ADC interrupt, and clear the
		 * status to put it back in to normal state.
		 */
		read_len = -ETIMEDOUT;
		goto adc_err;
	}
	mutex_unlock(&adc_priv->mutex);

	return read_len;

adc_err:
	regmap_update_bits(adc_priv->regmap, IPROC_INTERRUPT_MASK,
			   IPROC_ADC_INTR_MASK,
			   ((0x0 << channel) << IPROC_ADC_INTR));

	regmap_update_bits(adc_priv->regmap, IPROC_INTERRUPT_STATUS,
			   IPROC_ADC_INTR_MASK,
			   ((0x0 << channel) << IPROC_ADC_INTR));

	dev_err(&indio_dev->dev, "Timed out waiting for ADC data!\n");
	iproc_adc_reg_dump(indio_dev);
	mutex_unlock(&adc_priv->mutex);

	return read_len;
}