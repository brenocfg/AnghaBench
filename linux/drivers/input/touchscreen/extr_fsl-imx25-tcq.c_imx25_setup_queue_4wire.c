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
struct mx25_tcq_priv {int expected_samples; int sample_count; int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int MX25_ADCQ_ITEM (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MX25_ADCQ_ITEM_7_0 ; 
 int /*<<< orphan*/  MX25_CFG_PRECHARGE ; 
 int /*<<< orphan*/  MX25_CFG_TOUCH_DETECT ; 
 int /*<<< orphan*/  MX25_CFG_X_MEASUREMENT ; 
 int /*<<< orphan*/  MX25_CFG_Y_MEASUREMENT ; 
 int /*<<< orphan*/  imx25_setup_queue_cfgs (struct mx25_tcq_priv*,unsigned int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int imx25_setup_queue_4wire(struct mx25_tcq_priv *priv,
				   unsigned settling_cnt, int *items)
{
	imx25_setup_queue_cfgs(priv, settling_cnt);

	/* Setup the conversion queue */
	regmap_write(priv->regs, MX25_ADCQ_ITEM_7_0,
		     MX25_ADCQ_ITEM(0, MX25_CFG_PRECHARGE) |
		     MX25_ADCQ_ITEM(1, MX25_CFG_TOUCH_DETECT) |
		     MX25_ADCQ_ITEM(2, MX25_CFG_X_MEASUREMENT) |
		     MX25_ADCQ_ITEM(3, MX25_CFG_Y_MEASUREMENT) |
		     MX25_ADCQ_ITEM(4, MX25_CFG_PRECHARGE) |
		     MX25_ADCQ_ITEM(5, MX25_CFG_TOUCH_DETECT));

	/*
	 * We measure X/Y with 'sample_count' number of samples and execute a
	 * touch detection twice, with 1 sample each
	 */
	priv->expected_samples = priv->sample_count * 2 + 2;
	*items = 6;

	return 0;
}