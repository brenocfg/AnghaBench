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
typedef  int u32 ;
struct radio_isa_card {scalar_t__ io; } ;

/* Variables and functions */
 int /*<<< orphan*/  outb_p (unsigned long,scalar_t__) ; 

__attribute__((used)) static int typhoon_s_frequency(struct radio_isa_card *isa, u32 freq)
{
	unsigned long outval;
	unsigned long x;

	/*
	 * The frequency transfer curve is not linear. The best fit I could
	 * get is
	 *
	 * outval = -155 + exp((f + 15.55) * 0.057))
	 *
	 * where frequency f is in MHz. Since we don't have exp in the kernel,
	 * I approximate this function by a third order polynomial.
	 *
	 */

	x = freq / 160;
	outval = (x * x + 2500) / 5000;
	outval = (outval * x + 5000) / 10000;
	outval -= (10 * x * x + 10433) / 20866;
	outval += 4 * x - 11505;

	outb_p((outval >> 8) & 0x01, isa->io + 4);
	outb_p(outval >> 9, isa->io + 6);
	outb_p(outval & 0xff, isa->io + 8);
	return 0;
}