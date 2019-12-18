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
struct ad9834_state {int /*<<< orphan*/  freq_msg; int /*<<< orphan*/  spi; void** freq_data; int /*<<< orphan*/  mclk; } ;

/* Variables and functions */
 int AD9834_FREQ_BITS ; 
 int EINVAL ; 
 unsigned long RES_MASK (int) ; 
 unsigned long ad9834_calc_freqreg (unsigned long,unsigned long) ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 void* cpu_to_be16 (unsigned long) ; 
 int spi_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ad9834_write_frequency(struct ad9834_state *st,
				  unsigned long addr, unsigned long fout)
{
	unsigned long clk_freq;
	unsigned long regval;

	clk_freq = clk_get_rate(st->mclk);

	if (fout > (clk_freq / 2))
		return -EINVAL;

	regval = ad9834_calc_freqreg(clk_freq, fout);

	st->freq_data[0] = cpu_to_be16(addr | (regval &
				       RES_MASK(AD9834_FREQ_BITS / 2)));
	st->freq_data[1] = cpu_to_be16(addr | ((regval >>
				       (AD9834_FREQ_BITS / 2)) &
				       RES_MASK(AD9834_FREQ_BITS / 2)));

	return spi_sync(st->spi, &st->freq_msg);
}