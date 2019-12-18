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
typedef  int /*<<< orphan*/  u8 ;
typedef  unsigned long long u64 ;
struct ad5933_state {int mclk_hz; unsigned long freq_start; unsigned long freq_inc; int /*<<< orphan*/  client; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
#define  AD5933_REG_FREQ_INC 129 
#define  AD5933_REG_FREQ_START 128 
 int EINVAL ; 
 int ad5933_i2c_write (int /*<<< orphan*/ ,unsigned int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_be32 (unsigned long long) ; 
 int /*<<< orphan*/  do_div (unsigned long long,int) ; 

__attribute__((used)) static int ad5933_set_freq(struct ad5933_state *st,
			   unsigned int reg, unsigned long freq)
{
	unsigned long long freqreg;
	union {
		__be32 d32;
		u8 d8[4];
	} dat;

	freqreg = (u64)freq * (u64)(1 << 27);
	do_div(freqreg, st->mclk_hz / 4);

	switch (reg) {
	case AD5933_REG_FREQ_START:
		st->freq_start = freq;
		break;
	case AD5933_REG_FREQ_INC:
		st->freq_inc = freq;
		break;
	default:
		return -EINVAL;
	}

	dat.d32 = cpu_to_be32(freqreg);
	return ad5933_i2c_write(st->client, reg, 3, &dat.d8[1]);
}