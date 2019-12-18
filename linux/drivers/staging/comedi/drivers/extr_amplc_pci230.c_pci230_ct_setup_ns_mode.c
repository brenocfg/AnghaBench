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
typedef  int /*<<< orphan*/  u64 ;
struct comedi_device {int /*<<< orphan*/  pacer; scalar_t__ iobase; } ;

/* Variables and functions */
 scalar_t__ PCI230_ZCLK_SCE ; 
 int /*<<< orphan*/  comedi_8254_set_mode (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  comedi_8254_write (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 unsigned int pci230_choose_clk_count (int /*<<< orphan*/ ,unsigned int*,unsigned int) ; 
 int /*<<< orphan*/  pci230_clk_config (unsigned int,unsigned int) ; 

__attribute__((used)) static void pci230_ct_setup_ns_mode(struct comedi_device *dev, unsigned int ct,
				    unsigned int mode, u64 ns,
				    unsigned int flags)
{
	unsigned int clk_src;
	unsigned int count;

	/* Set mode. */
	comedi_8254_set_mode(dev->pacer, ct, mode);
	/* Determine clock source and count. */
	clk_src = pci230_choose_clk_count(ns, &count, flags);
	/* Program clock source. */
	outb(pci230_clk_config(ct, clk_src), dev->iobase + PCI230_ZCLK_SCE);
	/* Set initial count. */
	if (count >= 65536)
		count = 0;

	comedi_8254_write(dev->pacer, ct, count);
}