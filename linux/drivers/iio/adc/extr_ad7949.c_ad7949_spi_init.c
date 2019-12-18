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
struct ad7949_adc_chip {int /*<<< orphan*/  current_channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  AD7949_MASK_TOTAL ; 
 int /*<<< orphan*/  ad7949_spi_read_channel (struct ad7949_adc_chip*,int*,int /*<<< orphan*/ ) ; 
 int ad7949_spi_write_cfg (struct ad7949_adc_chip*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ad7949_spi_init(struct ad7949_adc_chip *ad7949_adc)
{
	int ret;
	int val;

	/* Sequencer disabled, CFG readback disabled, IN0 as default channel */
	ad7949_adc->current_channel = 0;
	ret = ad7949_spi_write_cfg(ad7949_adc, 0x3C79, AD7949_MASK_TOTAL);

	/*
	 * Do two dummy conversions to apply the first configuration setting.
	 * Required only after the start up of the device.
	 */
	ad7949_spi_read_channel(ad7949_adc, &val, ad7949_adc->current_channel);
	ad7949_spi_read_channel(ad7949_adc, &val, ad7949_adc->current_channel);

	return ret;
}