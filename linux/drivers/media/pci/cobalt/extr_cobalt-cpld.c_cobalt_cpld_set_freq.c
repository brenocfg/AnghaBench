#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  unsigned int u64 ;
typedef  unsigned int u32 ;
typedef  int u16 ;
struct cobalt {int dummy; } ;
typedef  int /*<<< orphan*/  read_regs ;
struct TYPE_3__ {unsigned int mult; int n1; int hsdiv; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 
 unsigned int DCO_MAX ; 
 unsigned int DCO_MIN ; 
 int S01755_REG_CLOCK_CTRL_BITMAP_CLKHSMA_EN ; 
 int S01755_REG_CLOCK_CTRL_BITMAP_CLKHSMA_FPGA_CTRL ; 
 int S01755_REG_CLOCK_CTRL_BITMAP_CLKHSMA_RST_TRIGGER ; 
 int S01755_REG_CLOCK_CTRL_BITMAP_CLKHSMA_WR_TRIGGER ; 
 int /*<<< orphan*/  SI570_CLOCK_CTRL ; 
 int /*<<< orphan*/  SI570_REG10 ; 
 int /*<<< orphan*/  SI570_REG11 ; 
 int /*<<< orphan*/  SI570_REG12 ; 
 int /*<<< orphan*/  SI570_REG7 ; 
 int /*<<< orphan*/  SI570_REG8 ; 
 int /*<<< orphan*/  SI570_REG9 ; 
 int /*<<< orphan*/  cobalt_dbg (int,char*,...) ; 
 int /*<<< orphan*/  cobalt_info (char*,int) ; 
 int cpld_read (struct cobalt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpld_write (struct cobalt*,int /*<<< orphan*/ ,int) ; 
 unsigned int div_u64 (unsigned int,unsigned int const) ; 
 int /*<<< orphan*/  div_u64_rem (unsigned int,unsigned int const,unsigned int*) ; 
 int /*<<< orphan*/  memcmp (int*,int*,int) ; 
 TYPE_1__* multipliers ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

bool cobalt_cpld_set_freq(struct cobalt *cobalt, unsigned f_out)
{
	const unsigned f_xtal = 39170000;	/* xtal for si598 */
	u64 dco;
	u64 rfreq;
	unsigned delta = 0xffffffff;
	unsigned i_best = 0;
	unsigned i;
	u8 n1, hsdiv;
	u8 regs[6];
	int found = 0;
	u16 clock_ctrl;
	int retries = 3;

	for (i = 0; i < ARRAY_SIZE(multipliers); i++) {
		unsigned mult = multipliers[i].mult;
		u32 d;

		dco = (u64)f_out * mult;
		if (dco < DCO_MIN || dco > DCO_MAX)
			continue;
		div_u64_rem((dco << 28) + f_xtal / 2, f_xtal, &d);
		if (d < delta) {
			found = 1;
			i_best = i;
			delta = d;
		}
	}
	if (!found)
		return false;
	dco = (u64)f_out * multipliers[i_best].mult;
	n1 = multipliers[i_best].n1 - 1;
	hsdiv = multipliers[i_best].hsdiv - 4;
	rfreq = div_u64(dco << 28, f_xtal);

	clock_ctrl = cpld_read(cobalt, SI570_CLOCK_CTRL);
	clock_ctrl |= S01755_REG_CLOCK_CTRL_BITMAP_CLKHSMA_FPGA_CTRL;
	clock_ctrl |= S01755_REG_CLOCK_CTRL_BITMAP_CLKHSMA_EN;

	regs[0] = (hsdiv << 5) | (n1 >> 2);
	regs[1] = ((n1 & 0x3) << 6) | (rfreq >> 32);
	regs[2] = (rfreq >> 24) & 0xff;
	regs[3] = (rfreq >> 16) & 0xff;
	regs[4] = (rfreq >> 8) & 0xff;
	regs[5] = rfreq & 0xff;

	/* The sequence of clock_ctrl flags to set is very weird. It looks
	   like I have to reset it, then set the new frequency and reset it
	   again. It shouldn't be necessary to do a reset, but if I don't,
	   then a strange frequency is set (156.412034 MHz, or register values
	   0x01, 0xc7, 0xfc, 0x7f, 0x53, 0x62).
	 */

	cobalt_dbg(1, "%u: %6ph\n", f_out, regs);

	while (retries--) {
		u8 read_regs[6];

		cpld_write(cobalt, SI570_CLOCK_CTRL,
			S01755_REG_CLOCK_CTRL_BITMAP_CLKHSMA_EN |
			S01755_REG_CLOCK_CTRL_BITMAP_CLKHSMA_FPGA_CTRL);
		usleep_range(10000, 15000);
		cpld_write(cobalt, SI570_REG7, regs[0]);
		cpld_write(cobalt, SI570_REG8, regs[1]);
		cpld_write(cobalt, SI570_REG9, regs[2]);
		cpld_write(cobalt, SI570_REG10, regs[3]);
		cpld_write(cobalt, SI570_REG11, regs[4]);
		cpld_write(cobalt, SI570_REG12, regs[5]);
		cpld_write(cobalt, SI570_CLOCK_CTRL,
			S01755_REG_CLOCK_CTRL_BITMAP_CLKHSMA_EN |
			S01755_REG_CLOCK_CTRL_BITMAP_CLKHSMA_WR_TRIGGER);
		usleep_range(10000, 15000);
		cpld_write(cobalt, SI570_CLOCK_CTRL,
			S01755_REG_CLOCK_CTRL_BITMAP_CLKHSMA_EN |
			S01755_REG_CLOCK_CTRL_BITMAP_CLKHSMA_FPGA_CTRL);
		usleep_range(10000, 15000);
		read_regs[0] = cpld_read(cobalt, SI570_REG7);
		read_regs[1] = cpld_read(cobalt, SI570_REG8);
		read_regs[2] = cpld_read(cobalt, SI570_REG9);
		read_regs[3] = cpld_read(cobalt, SI570_REG10);
		read_regs[4] = cpld_read(cobalt, SI570_REG11);
		read_regs[5] = cpld_read(cobalt, SI570_REG12);
		cpld_write(cobalt, SI570_CLOCK_CTRL,
			S01755_REG_CLOCK_CTRL_BITMAP_CLKHSMA_EN |
			S01755_REG_CLOCK_CTRL_BITMAP_CLKHSMA_FPGA_CTRL |
			S01755_REG_CLOCK_CTRL_BITMAP_CLKHSMA_RST_TRIGGER);
		usleep_range(10000, 15000);
		cpld_write(cobalt, SI570_CLOCK_CTRL,
			S01755_REG_CLOCK_CTRL_BITMAP_CLKHSMA_EN);
		usleep_range(10000, 15000);

		if (!memcmp(read_regs, regs, sizeof(read_regs)))
			break;
		cobalt_dbg(1, "retry: %6ph\n", read_regs);
	}
	if (2 - retries)
		cobalt_info("Needed %d retries\n", 2 - retries);

	return true;
}