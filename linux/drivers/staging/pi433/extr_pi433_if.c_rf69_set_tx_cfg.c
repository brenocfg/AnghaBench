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
struct pi433_tx_cfg {scalar_t__ enable_preamble; scalar_t__ enable_sync; scalar_t__ enable_length_byte; scalar_t__ enable_crc; int /*<<< orphan*/  sync_pattern; int /*<<< orphan*/  sync_length; int /*<<< orphan*/  preamble_length; int /*<<< orphan*/  tx_start_condition; int /*<<< orphan*/  mod_shaping; int /*<<< orphan*/  pa_ramp; int /*<<< orphan*/  dev_frequency; int /*<<< orphan*/  modulation; int /*<<< orphan*/  bit_rate; int /*<<< orphan*/  frequency; } ;
struct pi433_device {int /*<<< orphan*/  spi; } ;

/* Variables and functions */
 scalar_t__ OPTION_ON ; 
 int /*<<< orphan*/  packet_length_fix ; 
 int /*<<< orphan*/  packet_length_var ; 
 int rf69_disable_crc (int /*<<< orphan*/ ) ; 
 int rf69_disable_sync (int /*<<< orphan*/ ) ; 
 int rf69_enable_crc (int /*<<< orphan*/ ) ; 
 int rf69_enable_sync (int /*<<< orphan*/ ) ; 
 int rf69_set_bit_rate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rf69_set_deviation (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rf69_set_frequency (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rf69_set_modulation (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rf69_set_modulation_shaping (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rf69_set_pa_ramp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rf69_set_packet_format (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rf69_set_preamble_length (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rf69_set_sync_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rf69_set_sync_values (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rf69_set_tx_start_condition (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
rf69_set_tx_cfg(struct pi433_device *dev, struct pi433_tx_cfg *tx_cfg)
{
	int ret;

	ret = rf69_set_frequency(dev->spi, tx_cfg->frequency);
	if (ret < 0)
		return ret;
	ret = rf69_set_bit_rate(dev->spi, tx_cfg->bit_rate);
	if (ret < 0)
		return ret;
	ret = rf69_set_modulation(dev->spi, tx_cfg->modulation);
	if (ret < 0)
		return ret;
	ret = rf69_set_deviation(dev->spi, tx_cfg->dev_frequency);
	if (ret < 0)
		return ret;
	ret = rf69_set_pa_ramp(dev->spi, tx_cfg->pa_ramp);
	if (ret < 0)
		return ret;
	ret = rf69_set_modulation_shaping(dev->spi, tx_cfg->mod_shaping);
	if (ret < 0)
		return ret;
	ret = rf69_set_tx_start_condition(dev->spi, tx_cfg->tx_start_condition);
	if (ret < 0)
		return ret;

	/* packet format enable */
	if (tx_cfg->enable_preamble == OPTION_ON) {
		ret = rf69_set_preamble_length(dev->spi,
					       tx_cfg->preamble_length);
		if (ret < 0)
			return ret;
	} else {
		ret = rf69_set_preamble_length(dev->spi, 0);
		if (ret < 0)
			return ret;
	}

	if (tx_cfg->enable_sync == OPTION_ON) {
		ret = rf69_set_sync_size(dev->spi, tx_cfg->sync_length);
		if (ret < 0)
			return ret;
		ret = rf69_set_sync_values(dev->spi, tx_cfg->sync_pattern);
		if (ret < 0)
			return ret;
		ret = rf69_enable_sync(dev->spi);
		if (ret < 0)
			return ret;
	} else {
		ret = rf69_disable_sync(dev->spi);
		if (ret < 0)
			return ret;
	}

	if (tx_cfg->enable_length_byte == OPTION_ON) {
		ret = rf69_set_packet_format(dev->spi, packet_length_var);
		if (ret < 0)
			return ret;
	} else {
		ret = rf69_set_packet_format(dev->spi, packet_length_fix);
		if (ret < 0)
			return ret;
	}

	if (tx_cfg->enable_crc == OPTION_ON) {
		ret = rf69_enable_crc(dev->spi);
		if (ret < 0)
			return ret;
	} else {
		ret = rf69_disable_crc(dev->spi);
		if (ret < 0)
			return ret;
	}

	return 0;
}