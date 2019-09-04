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
typedef  int uint32_t ;
struct fsmc_nand_timings {int tclr; int tar; int thiz; int thold; int twait; int tset; } ;
struct TYPE_2__ {int options; } ;
struct fsmc_nand_data {scalar_t__ regs_va; TYPE_1__ nand; } ;

/* Variables and functions */
 scalar_t__ ATTRIB ; 
 scalar_t__ COMM ; 
 int FSMC_DEVTYPE_NAND ; 
 int FSMC_DEVWID_16 ; 
 int FSMC_DEVWID_8 ; 
 int FSMC_ENABLE ; 
 scalar_t__ FSMC_PC ; 
 int FSMC_TAR_MASK ; 
 int FSMC_TAR_SHIFT ; 
 int FSMC_TCLR_MASK ; 
 int FSMC_TCLR_SHIFT ; 
 int FSMC_THIZ_MASK ; 
 int FSMC_THIZ_SHIFT ; 
 int FSMC_THOLD_MASK ; 
 int FSMC_THOLD_SHIFT ; 
 int FSMC_TSET_MASK ; 
 int FSMC_TSET_SHIFT ; 
 int FSMC_TWAIT_MASK ; 
 int FSMC_TWAIT_SHIFT ; 
 int FSMC_WAITON ; 
 int NAND_BUSWIDTH_16 ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void fsmc_nand_setup(struct fsmc_nand_data *host,
			    struct fsmc_nand_timings *tims)
{
	uint32_t value = FSMC_DEVTYPE_NAND | FSMC_ENABLE | FSMC_WAITON;
	uint32_t tclr, tar, thiz, thold, twait, tset;

	tclr = (tims->tclr & FSMC_TCLR_MASK) << FSMC_TCLR_SHIFT;
	tar = (tims->tar & FSMC_TAR_MASK) << FSMC_TAR_SHIFT;
	thiz = (tims->thiz & FSMC_THIZ_MASK) << FSMC_THIZ_SHIFT;
	thold = (tims->thold & FSMC_THOLD_MASK) << FSMC_THOLD_SHIFT;
	twait = (tims->twait & FSMC_TWAIT_MASK) << FSMC_TWAIT_SHIFT;
	tset = (tims->tset & FSMC_TSET_MASK) << FSMC_TSET_SHIFT;

	if (host->nand.options & NAND_BUSWIDTH_16)
		writel_relaxed(value | FSMC_DEVWID_16,
			       host->regs_va + FSMC_PC);
	else
		writel_relaxed(value | FSMC_DEVWID_8, host->regs_va + FSMC_PC);

	writel_relaxed(readl(host->regs_va + FSMC_PC) | tclr | tar,
		       host->regs_va + FSMC_PC);
	writel_relaxed(thiz | thold | twait | tset, host->regs_va + COMM);
	writel_relaxed(thiz | thold | twait | tset, host->regs_va + ATTRIB);
}