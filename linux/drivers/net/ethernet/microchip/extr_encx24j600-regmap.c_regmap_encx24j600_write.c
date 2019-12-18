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
typedef  int u8 ;

/* Variables and functions */
 int EINVAL ; 
 int regmap_encx24j600_sfr_write (void*,int,int*,size_t) ; 
 int regmap_encx24j600_spi_write (void*,int,int*,size_t) ; 

__attribute__((used)) static int regmap_encx24j600_write(void *context, const void *data,
				   size_t len)
{
	u8 *dout = (u8 *)data;
	u8 reg = dout[0];
	++dout;
	--len;

	if (reg > 0xa0)
		return regmap_encx24j600_spi_write(context, reg, dout, len);

	if (len > 2)
		return -EINVAL;

	return regmap_encx24j600_sfr_write(context, reg, dout, len);
}