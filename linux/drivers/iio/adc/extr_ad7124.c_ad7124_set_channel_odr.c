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
struct ad7124_state {TYPE_1__* channel_config; int /*<<< orphan*/  mclk; } ;
struct TYPE_2__ {void* odr; } ;

/* Variables and functions */
 int /*<<< orphan*/  AD7124_FILTER (unsigned int) ; 
 int /*<<< orphan*/  AD7124_FILTER_FS (unsigned int) ; 
 int /*<<< orphan*/  AD7124_FILTER_FS_MSK ; 
 void* DIV_ROUND_CLOSEST (unsigned int,unsigned int) ; 
 int ad7124_spi_write_mask (struct ad7124_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 unsigned int clk_get_rate (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ad7124_set_channel_odr(struct ad7124_state *st,
				  unsigned int channel,
				  unsigned int odr)
{
	unsigned int fclk, odr_sel_bits;
	int ret;

	fclk = clk_get_rate(st->mclk);
	/*
	 * FS[10:0] = fCLK / (fADC x 32) where:
	 * fADC is the output data rate
	 * fCLK is the master clock frequency
	 * FS[10:0] are the bits in the filter register
	 * FS[10:0] can have a value from 1 to 2047
	 */
	odr_sel_bits = DIV_ROUND_CLOSEST(fclk, odr * 32);
	if (odr_sel_bits < 1)
		odr_sel_bits = 1;
	else if (odr_sel_bits > 2047)
		odr_sel_bits = 2047;

	ret = ad7124_spi_write_mask(st, AD7124_FILTER(channel),
				    AD7124_FILTER_FS_MSK,
				    AD7124_FILTER_FS(odr_sel_bits), 3);
	if (ret < 0)
		return ret;
	/* fADC = fCLK / (FS[10:0] x 32) */
	st->channel_config[channel].odr =
		DIV_ROUND_CLOSEST(fclk, odr_sel_bits * 32);

	return 0;
}