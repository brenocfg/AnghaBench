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
struct ad7949_adc_chip {int resolution; } ;

/* Variables and functions */
 scalar_t__ AD7949_CFG_REG_SIZE_BITS ; 
 scalar_t__ ad7949_spi_cfg_is_read_back (struct ad7949_adc_chip*) ; 

__attribute__((used)) static int ad7949_spi_bits_per_word(struct ad7949_adc_chip *ad7949_adc)
{
	int ret = ad7949_adc->resolution;

	if (ad7949_spi_cfg_is_read_back(ad7949_adc))
		ret += AD7949_CFG_REG_SIZE_BITS;

	return ret;
}