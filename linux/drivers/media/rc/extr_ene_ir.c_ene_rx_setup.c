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
struct ene_device {scalar_t__ pll_freq; scalar_t__ hw_revision; int hw_use_gpio_0a; int rx_fan_input_inuse; TYPE_1__* rdev; scalar_t__ hw_learning_and_tx_capable; scalar_t__ hw_fan_input; scalar_t__ carrier_detect_enabled; scalar_t__ learning_mode_enabled; } ;
struct TYPE_2__ {scalar_t__ min_timeout; scalar_t__ max_timeout; scalar_t__ timeout; void* tx_resolution; void* rx_resolution; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENE_CIRCAR_PULS ; 
 int /*<<< orphan*/  ENE_CIRCFG ; 
 int /*<<< orphan*/  ENE_CIRCFG2 ; 
 int /*<<< orphan*/  ENE_CIRCFG2_CARR_DETECT ; 
 int /*<<< orphan*/  ENE_CIRCFG_CARR_DEMOD ; 
 int /*<<< orphan*/  ENE_CIRRLC_CFG ; 
 int ENE_CIRRLC_CFG_OVERFLOW ; 
 scalar_t__ ENE_DEFAULT_PLL_FREQ ; 
 int ENE_DEFAULT_SAMPLE_PERIOD ; 
 int ENE_FW_SAMPLE_PERIOD_FAN ; 
 int ENE_FW_SMPL_BUF_FAN_MSK ; 
 scalar_t__ ENE_HW_C ; 
 void* US_TO_NS (int) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dbg (char*,int) ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  ene_clear_reg_mask (struct ene_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ene_rx_select_input (struct ene_device*,int) ; 
 int /*<<< orphan*/  ene_set_clear_reg_mask (struct ene_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ene_set_reg_mask (struct ene_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ene_write_reg (struct ene_device*,int /*<<< orphan*/ ,int) ; 
 int sample_period ; 

__attribute__((used)) static void ene_rx_setup(struct ene_device *dev)
{
	bool learning_mode = dev->learning_mode_enabled ||
					dev->carrier_detect_enabled;
	int sample_period_adjust = 0;

	dbg("RX: setup receiver, learning mode = %d", learning_mode);


	/* This selects RLC input and clears CFG2 settings */
	ene_write_reg(dev, ENE_CIRCFG2, 0x00);

	/* set sample period*/
	if (sample_period == ENE_DEFAULT_SAMPLE_PERIOD)
		sample_period_adjust =
			dev->pll_freq == ENE_DEFAULT_PLL_FREQ ? 1 : 2;

	ene_write_reg(dev, ENE_CIRRLC_CFG,
			(sample_period + sample_period_adjust) |
						ENE_CIRRLC_CFG_OVERFLOW);
	/* revB doesn't support inputs */
	if (dev->hw_revision < ENE_HW_C)
		goto select_timeout;

	if (learning_mode) {

		WARN_ON(!dev->hw_learning_and_tx_capable);

		/* Enable the opposite of the normal input
		That means that if GPIO40 is normally used, use GPIO0A
		and vice versa.
		This input will carry non demodulated
		signal, and we will tell the hw to demodulate it itself */
		ene_rx_select_input(dev, !dev->hw_use_gpio_0a);
		dev->rx_fan_input_inuse = false;

		/* Enable carrier demodulation */
		ene_set_reg_mask(dev, ENE_CIRCFG, ENE_CIRCFG_CARR_DEMOD);

		/* Enable carrier detection */
		ene_write_reg(dev, ENE_CIRCAR_PULS, 0x63);
		ene_set_clear_reg_mask(dev, ENE_CIRCFG2, ENE_CIRCFG2_CARR_DETECT,
			dev->carrier_detect_enabled || debug);
	} else {
		if (dev->hw_fan_input)
			dev->rx_fan_input_inuse = true;
		else
			ene_rx_select_input(dev, dev->hw_use_gpio_0a);

		/* Disable carrier detection & demodulation */
		ene_clear_reg_mask(dev, ENE_CIRCFG, ENE_CIRCFG_CARR_DEMOD);
		ene_clear_reg_mask(dev, ENE_CIRCFG2, ENE_CIRCFG2_CARR_DETECT);
	}

select_timeout:
	if (dev->rx_fan_input_inuse) {
		dev->rdev->rx_resolution = US_TO_NS(ENE_FW_SAMPLE_PERIOD_FAN);

		/* Fan input doesn't support timeouts, it just ends the
			input with a maximum sample */
		dev->rdev->min_timeout = dev->rdev->max_timeout =
			US_TO_NS(ENE_FW_SMPL_BUF_FAN_MSK *
				ENE_FW_SAMPLE_PERIOD_FAN);
	} else {
		dev->rdev->rx_resolution = US_TO_NS(sample_period);

		/* Theoreticly timeout is unlimited, but we cap it
		 * because it was seen that on one device, it
		 * would stop sending spaces after around 250 msec.
		 * Besides, this is close to 2^32 anyway and timeout is u32.
		 */
		dev->rdev->min_timeout = US_TO_NS(127 * sample_period);
		dev->rdev->max_timeout = US_TO_NS(200000);
	}

	if (dev->hw_learning_and_tx_capable)
		dev->rdev->tx_resolution = US_TO_NS(sample_period);

	if (dev->rdev->timeout > dev->rdev->max_timeout)
		dev->rdev->timeout = dev->rdev->max_timeout;
	if (dev->rdev->timeout < dev->rdev->min_timeout)
		dev->rdev->timeout = dev->rdev->min_timeout;
}