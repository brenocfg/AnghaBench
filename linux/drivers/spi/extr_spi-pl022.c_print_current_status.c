#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* u32 ;
typedef  void* u16 ;
struct pl022 {TYPE_2__* vendor; int /*<<< orphan*/  exp_fifo_level; TYPE_1__* adev; int /*<<< orphan*/  virtbase; } ;
struct TYPE_4__ {int /*<<< orphan*/  fifodepth; scalar_t__ extended_cr; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSP_CR0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSP_CR1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSP_DMACR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSP_SR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,...) ; 
 void* readl (int /*<<< orphan*/ ) ; 
 void* readw (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void print_current_status(struct pl022 *pl022)
{
	u32 read_cr0;
	u16 read_cr1, read_dmacr, read_sr;

	if (pl022->vendor->extended_cr)
		read_cr0 = readl(SSP_CR0(pl022->virtbase));
	else
		read_cr0 = readw(SSP_CR0(pl022->virtbase));
	read_cr1 = readw(SSP_CR1(pl022->virtbase));
	read_dmacr = readw(SSP_DMACR(pl022->virtbase));
	read_sr = readw(SSP_SR(pl022->virtbase));

	dev_warn(&pl022->adev->dev, "spi-pl022 CR0: %x\n", read_cr0);
	dev_warn(&pl022->adev->dev, "spi-pl022 CR1: %x\n", read_cr1);
	dev_warn(&pl022->adev->dev, "spi-pl022 DMACR: %x\n", read_dmacr);
	dev_warn(&pl022->adev->dev, "spi-pl022 SR: %x\n", read_sr);
	dev_warn(&pl022->adev->dev,
			"spi-pl022 exp_fifo_level/fifodepth: %u/%d\n",
			pl022->exp_fifo_level,
			pl022->vendor->fifodepth);

}