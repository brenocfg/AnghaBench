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
struct ad7949_adc_chip {int cfg; } ;

/* Variables and functions */
 int AD7949_CFG_READ_BACK ; 

__attribute__((used)) static bool ad7949_spi_cfg_is_read_back(struct ad7949_adc_chip *ad7949_adc)
{
	if (!(ad7949_adc->cfg & AD7949_CFG_READ_BACK))
		return true;

	return false;
}