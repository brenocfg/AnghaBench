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
struct mxs_lradc_adc {scalar_t__ base; int /*<<< orphan*/  completion; int /*<<< orphan*/  is_divided; struct mxs_lradc* lradc; } ;
struct mxs_lradc {scalar_t__ soc; } ;
struct iio_dev {int dummy; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  HZ ; 
 int IIO_VAL_INT ; 
 scalar_t__ IMX28_LRADC ; 
 scalar_t__ LRADC_CH (int /*<<< orphan*/ ) ; 
 int LRADC_CH_VALUE_MASK ; 
 scalar_t__ LRADC_CTRL0 ; 
 scalar_t__ LRADC_CTRL1 ; 
 int LRADC_CTRL1_LRADC_IRQ_EN (int /*<<< orphan*/ ) ; 
 scalar_t__ LRADC_CTRL2 ; 
 int LRADC_CTRL2_DIVIDE_BY_TWO_OFFSET ; 
 scalar_t__ LRADC_CTRL4 ; 
 int LRADC_CTRL4_LRADCSELECT_MASK (int /*<<< orphan*/ ) ; 
 scalar_t__ STMP_OFFSET_REG_CLR ; 
 scalar_t__ STMP_OFFSET_REG_SET ; 
 int iio_device_claim_direct_mode (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_device_release_direct_mode (struct iio_dev*) ; 
 struct mxs_lradc_adc* iio_priv (struct iio_dev*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int,int /*<<< orphan*/ *) ; 
 int wait_for_completion_killable_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int mxs_lradc_adc_read_single(struct iio_dev *iio_dev, int chan,
				     int *val)
{
	struct mxs_lradc_adc *adc = iio_priv(iio_dev);
	struct mxs_lradc *lradc = adc->lradc;
	int ret;

	/*
	 * See if there is no buffered operation in progress. If there is simply
	 * bail out. This can be improved to support both buffered and raw IO at
	 * the same time, yet the code becomes horribly complicated. Therefore I
	 * applied KISS principle here.
	 */
	ret = iio_device_claim_direct_mode(iio_dev);
	if (ret)
		return ret;

	reinit_completion(&adc->completion);

	/*
	 * No buffered operation in progress, map the channel and trigger it.
	 * Virtual channel 0 is always used here as the others are always not
	 * used if doing raw sampling.
	 */
	if (lradc->soc == IMX28_LRADC)
		writel(LRADC_CTRL1_LRADC_IRQ_EN(0),
		       adc->base + LRADC_CTRL1 + STMP_OFFSET_REG_CLR);
	writel(0x1, adc->base + LRADC_CTRL0 + STMP_OFFSET_REG_CLR);

	/* Enable / disable the divider per requirement */
	if (test_bit(chan, &adc->is_divided))
		writel(1 << LRADC_CTRL2_DIVIDE_BY_TWO_OFFSET,
		       adc->base + LRADC_CTRL2 + STMP_OFFSET_REG_SET);
	else
		writel(1 << LRADC_CTRL2_DIVIDE_BY_TWO_OFFSET,
		       adc->base + LRADC_CTRL2 + STMP_OFFSET_REG_CLR);

	/* Clean the slot's previous content, then set new one. */
	writel(LRADC_CTRL4_LRADCSELECT_MASK(0),
	       adc->base + LRADC_CTRL4 + STMP_OFFSET_REG_CLR);
	writel(chan, adc->base + LRADC_CTRL4 + STMP_OFFSET_REG_SET);

	writel(0, adc->base + LRADC_CH(0));

	/* Enable the IRQ and start sampling the channel. */
	writel(LRADC_CTRL1_LRADC_IRQ_EN(0),
	       adc->base + LRADC_CTRL1 + STMP_OFFSET_REG_SET);
	writel(BIT(0), adc->base + LRADC_CTRL0 + STMP_OFFSET_REG_SET);

	/* Wait for completion on the channel, 1 second max. */
	ret = wait_for_completion_killable_timeout(&adc->completion, HZ);
	if (!ret)
		ret = -ETIMEDOUT;
	if (ret < 0)
		goto err;

	/* Read the data. */
	*val = readl(adc->base + LRADC_CH(0)) & LRADC_CH_VALUE_MASK;
	ret = IIO_VAL_INT;

err:
	writel(LRADC_CTRL1_LRADC_IRQ_EN(0),
	       adc->base + LRADC_CTRL1 + STMP_OFFSET_REG_CLR);

	iio_device_release_direct_mode(iio_dev);

	return ret;
}