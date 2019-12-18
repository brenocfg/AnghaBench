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
struct pi433_rx_cfg {scalar_t__ enable_sync; scalar_t__ enable_length_byte; scalar_t__ enable_address_filtering; scalar_t__ enable_crc; int fixed_message_length; int /*<<< orphan*/  broadcast_address; int /*<<< orphan*/  node_address; int /*<<< orphan*/  sync_pattern; int /*<<< orphan*/  sync_length; int /*<<< orphan*/  bytes_to_drop; int /*<<< orphan*/  dagc; int /*<<< orphan*/  bw_exponent; int /*<<< orphan*/  bw_mantisse; int /*<<< orphan*/  threshold_decrement; int /*<<< orphan*/  rssi_threshold; int /*<<< orphan*/  antenna_impedance; int /*<<< orphan*/  modulation; int /*<<< orphan*/  bit_rate; int /*<<< orphan*/  frequency; } ;
struct pi433_device {int /*<<< orphan*/  spi; int /*<<< orphan*/  rx_bytes_to_drop; } ;

/* Variables and functions */
 scalar_t__ OPTION_ON ; 
 int /*<<< orphan*/  after_sync_interrupt ; 
 int /*<<< orphan*/  always ; 
 scalar_t__ filtering_off ; 
 int /*<<< orphan*/  packet_length_fix ; 
 int /*<<< orphan*/  packet_length_var ; 
 int rf69_disable_crc (int /*<<< orphan*/ ) ; 
 int rf69_disable_sync (int /*<<< orphan*/ ) ; 
 int rf69_enable_crc (int /*<<< orphan*/ ) ; 
 int rf69_enable_sync (int /*<<< orphan*/ ) ; 
 int rf69_set_address_filtering (int /*<<< orphan*/ ,scalar_t__) ; 
 int rf69_set_antenna_impedance (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rf69_set_bandwidth (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rf69_set_bandwidth_during_afc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rf69_set_bit_rate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rf69_set_broadcast_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rf69_set_dagc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rf69_set_fifo_fill_condition (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rf69_set_frequency (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rf69_set_modulation (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rf69_set_node_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rf69_set_ook_threshold_dec (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rf69_set_packet_format (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rf69_set_payload_length (int /*<<< orphan*/ ,int) ; 
 int rf69_set_rssi_threshold (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rf69_set_sync_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rf69_set_sync_values (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
rf69_set_rx_cfg(struct pi433_device *dev, struct pi433_rx_cfg *rx_cfg)
{
	int ret;
	int payload_length;

	/* receiver config */
	ret = rf69_set_frequency(dev->spi, rx_cfg->frequency);
	if (ret < 0)
		return ret;
	ret = rf69_set_bit_rate(dev->spi, rx_cfg->bit_rate);
	if (ret < 0)
		return ret;
	ret = rf69_set_modulation(dev->spi, rx_cfg->modulation);
	if (ret < 0)
		return ret;
	ret = rf69_set_antenna_impedance(dev->spi, rx_cfg->antenna_impedance);
	if (ret < 0)
		return ret;
	ret = rf69_set_rssi_threshold(dev->spi, rx_cfg->rssi_threshold);
	if (ret < 0)
		return ret;
	ret = rf69_set_ook_threshold_dec(dev->spi, rx_cfg->threshold_decrement);
	if (ret < 0)
		return ret;
	ret = rf69_set_bandwidth(dev->spi, rx_cfg->bw_mantisse,
				 rx_cfg->bw_exponent);
	if (ret < 0)
		return ret;
	ret = rf69_set_bandwidth_during_afc(dev->spi, rx_cfg->bw_mantisse,
					    rx_cfg->bw_exponent);
	if (ret < 0)
		return ret;
	ret = rf69_set_dagc(dev->spi, rx_cfg->dagc);
	if (ret < 0)
		return ret;

	dev->rx_bytes_to_drop = rx_cfg->bytes_to_drop;

	/* packet config */
	/* enable */
	if (rx_cfg->enable_sync == OPTION_ON) {
		ret = rf69_enable_sync(dev->spi);
		if (ret < 0)
			return ret;

		ret = rf69_set_fifo_fill_condition(dev->spi,
						   after_sync_interrupt);
		if (ret < 0)
			return ret;
	} else {
		ret = rf69_disable_sync(dev->spi);
		if (ret < 0)
			return ret;

		ret = rf69_set_fifo_fill_condition(dev->spi, always);
		if (ret < 0)
			return ret;
	}
	if (rx_cfg->enable_length_byte == OPTION_ON) {
		ret = rf69_set_packet_format(dev->spi, packet_length_var);
		if (ret < 0)
			return ret;
	} else {
		ret = rf69_set_packet_format(dev->spi, packet_length_fix);
		if (ret < 0)
			return ret;
	}
	ret = rf69_set_address_filtering(dev->spi,
					 rx_cfg->enable_address_filtering);
	if (ret < 0)
		return ret;

	if (rx_cfg->enable_crc == OPTION_ON) {
		ret = rf69_enable_crc(dev->spi);
		if (ret < 0)
			return ret;
	} else {
		ret = rf69_disable_crc(dev->spi);
		if (ret < 0)
			return ret;
	}

	/* lengths */
	ret = rf69_set_sync_size(dev->spi, rx_cfg->sync_length);
	if (ret < 0)
		return ret;
	if (rx_cfg->enable_length_byte == OPTION_ON) {
		ret = rf69_set_payload_length(dev->spi, 0xff);
		if (ret < 0)
			return ret;
	} else if (rx_cfg->fixed_message_length != 0) {
		payload_length = rx_cfg->fixed_message_length;
		if (rx_cfg->enable_length_byte  == OPTION_ON)
			payload_length++;
		if (rx_cfg->enable_address_filtering != filtering_off)
			payload_length++;
		ret = rf69_set_payload_length(dev->spi, payload_length);
		if (ret < 0)
			return ret;
	} else {
		ret = rf69_set_payload_length(dev->spi, 0);
		if (ret < 0)
			return ret;
	}

	/* values */
	if (rx_cfg->enable_sync == OPTION_ON) {
		ret = rf69_set_sync_values(dev->spi, rx_cfg->sync_pattern);
		if (ret < 0)
			return ret;
	}
	if (rx_cfg->enable_address_filtering != filtering_off) {
		ret = rf69_set_node_address(dev->spi, rx_cfg->node_address);
		if (ret < 0)
			return ret;
		ret = rf69_set_broadcast_address(dev->spi,
						 rx_cfg->broadcast_address);
		if (ret < 0)
			return ret;
	}

	return 0;
}