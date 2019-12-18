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
typedef  int u16 ;
struct ad5761_state {int range; scalar_t__ use_intref; } ;
typedef  enum ad5761_voltage_range { ____Placeholder_ad5761_voltage_range } ad5761_voltage_range ;

/* Variables and functions */
 int /*<<< orphan*/  AD5761_ADDR_CTRL_WRITE_REG ; 
 int /*<<< orphan*/  AD5761_ADDR_SW_FULL_RESET ; 
 int AD5761_CTRL_ETS ; 
 int AD5761_CTRL_USE_INTVREF ; 
 int _ad5761_spi_write (struct ad5761_state*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ad5761_spi_set_range(struct ad5761_state *st,
				enum ad5761_voltage_range range)
{
	u16 aux;
	int ret;

	aux = (range & 0x7) | AD5761_CTRL_ETS;

	if (st->use_intref)
		aux |= AD5761_CTRL_USE_INTVREF;

	ret = _ad5761_spi_write(st, AD5761_ADDR_SW_FULL_RESET, 0);
	if (ret)
		return ret;

	ret = _ad5761_spi_write(st, AD5761_ADDR_CTRL_WRITE_REG, aux);
	if (ret)
		return ret;

	st->range = range;

	return 0;
}