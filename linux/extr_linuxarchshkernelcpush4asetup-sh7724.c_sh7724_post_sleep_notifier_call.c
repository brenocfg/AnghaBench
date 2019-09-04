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
struct notifier_block {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  spuclk; int /*<<< orphan*/  irdaclk; int /*<<< orphan*/  rwtcsr; int /*<<< orphan*/  rwtcnt; int /*<<< orphan*/  imr12; int /*<<< orphan*/  imr11; int /*<<< orphan*/  imr10; int /*<<< orphan*/  imr9; int /*<<< orphan*/  imr8; int /*<<< orphan*/  imr7; int /*<<< orphan*/  imr6; int /*<<< orphan*/  imr5; int /*<<< orphan*/  imr4; int /*<<< orphan*/  imr3; int /*<<< orphan*/  imr2; int /*<<< orphan*/  imr1; int /*<<< orphan*/  imr0; int /*<<< orphan*/  iprl; int /*<<< orphan*/  iprk; int /*<<< orphan*/  iprj; int /*<<< orphan*/  ipri; int /*<<< orphan*/  iprh; int /*<<< orphan*/  iprg; int /*<<< orphan*/  iprf; int /*<<< orphan*/  ipre; int /*<<< orphan*/  iprd; int /*<<< orphan*/  iprc; int /*<<< orphan*/  iprb; int /*<<< orphan*/  ipra; int /*<<< orphan*/  cs6bwcr; int /*<<< orphan*/  cs6awcr; int /*<<< orphan*/  cs5bwcr; int /*<<< orphan*/  cs5awcr; int /*<<< orphan*/  cs4wcr; int /*<<< orphan*/  cs6bbcr; int /*<<< orphan*/  cs6abcr; int /*<<< orphan*/  cs5bbcr; int /*<<< orphan*/  cs5abcr; int /*<<< orphan*/  cs4bcr; int /*<<< orphan*/  cs0bcr; int /*<<< orphan*/  mmselr; } ;

/* Variables and functions */
 int NOTIFY_DONE ; 
 unsigned long SUSP_SH_RSTANDBY ; 
 int /*<<< orphan*/  __raw_writeb (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  __raw_writel (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  __raw_writew (int /*<<< orphan*/ ,int) ; 
 TYPE_1__ sh7724_rstandby_state ; 

__attribute__((used)) static int sh7724_post_sleep_notifier_call(struct notifier_block *nb,
					   unsigned long flags, void *unused)
{
	if (!(flags & SUSP_SH_RSTANDBY))
		return NOTIFY_DONE;

	/* BCR */
	__raw_writel(sh7724_rstandby_state.mmselr, 0xff800020); /* MMSELR */
	__raw_writel(sh7724_rstandby_state.cs0bcr, 0xfec10004); /* CS0BCR */
	__raw_writel(sh7724_rstandby_state.cs4bcr, 0xfec10010); /* CS4BCR */
	__raw_writel(sh7724_rstandby_state.cs5abcr, 0xfec10014); /* CS5ABCR */
	__raw_writel(sh7724_rstandby_state.cs5bbcr, 0xfec10018); /* CS5BBCR */
	__raw_writel(sh7724_rstandby_state.cs6abcr, 0xfec1001c); /* CS6ABCR */
	__raw_writel(sh7724_rstandby_state.cs6bbcr, 0xfec10020); /* CS6BBCR */
	__raw_writel(sh7724_rstandby_state.cs4wcr, 0xfec10030); /* CS4WCR */
	__raw_writel(sh7724_rstandby_state.cs5awcr, 0xfec10034); /* CS5AWCR */
	__raw_writel(sh7724_rstandby_state.cs5bwcr, 0xfec10038); /* CS5BWCR */
	__raw_writel(sh7724_rstandby_state.cs6awcr, 0xfec1003c); /* CS6AWCR */
	__raw_writel(sh7724_rstandby_state.cs6bwcr, 0xfec10040); /* CS6BWCR */

	/* INTC */
	__raw_writew(sh7724_rstandby_state.ipra, 0xa4080000); /* IPRA */
	__raw_writew(sh7724_rstandby_state.iprb, 0xa4080004); /* IPRB */
	__raw_writew(sh7724_rstandby_state.iprc, 0xa4080008); /* IPRC */
	__raw_writew(sh7724_rstandby_state.iprd, 0xa408000c); /* IPRD */
	__raw_writew(sh7724_rstandby_state.ipre, 0xa4080010); /* IPRE */
	__raw_writew(sh7724_rstandby_state.iprf, 0xa4080014); /* IPRF */
	__raw_writew(sh7724_rstandby_state.iprg, 0xa4080018); /* IPRG */
	__raw_writew(sh7724_rstandby_state.iprh, 0xa408001c); /* IPRH */
	__raw_writew(sh7724_rstandby_state.ipri, 0xa4080020); /* IPRI */
	__raw_writew(sh7724_rstandby_state.iprj, 0xa4080024); /* IPRJ */
	__raw_writew(sh7724_rstandby_state.iprk, 0xa4080028); /* IPRK */
	__raw_writew(sh7724_rstandby_state.iprl, 0xa408002c); /* IPRL */
	__raw_writeb(sh7724_rstandby_state.imr0, 0xa4080080); /* IMR0 */
	__raw_writeb(sh7724_rstandby_state.imr1, 0xa4080084); /* IMR1 */
	__raw_writeb(sh7724_rstandby_state.imr2, 0xa4080088); /* IMR2 */
	__raw_writeb(sh7724_rstandby_state.imr3, 0xa408008c); /* IMR3 */
	__raw_writeb(sh7724_rstandby_state.imr4, 0xa4080090); /* IMR4 */
	__raw_writeb(sh7724_rstandby_state.imr5, 0xa4080094); /* IMR5 */
	__raw_writeb(sh7724_rstandby_state.imr6, 0xa4080098); /* IMR6 */
	__raw_writeb(sh7724_rstandby_state.imr7, 0xa408009c); /* IMR7 */
	__raw_writeb(sh7724_rstandby_state.imr8, 0xa40800a0); /* IMR8 */
	__raw_writeb(sh7724_rstandby_state.imr9, 0xa40800a4); /* IMR9 */
	__raw_writeb(sh7724_rstandby_state.imr10, 0xa40800a8); /* IMR10 */
	__raw_writeb(sh7724_rstandby_state.imr11, 0xa40800ac); /* IMR11 */
	__raw_writeb(sh7724_rstandby_state.imr12, 0xa40800b0); /* IMR12 */

	/* RWDT */
	__raw_writew(sh7724_rstandby_state.rwtcnt, 0xa4520000); /* RWTCNT */
	__raw_writew(sh7724_rstandby_state.rwtcsr, 0xa4520004); /* RWTCSR */

	/* CPG */
	__raw_writel(sh7724_rstandby_state.irdaclk, 0xa4150018); /* IRDACLKCR */
	__raw_writel(sh7724_rstandby_state.spuclk, 0xa415003c); /* SPUCLKCR */

	return NOTIFY_DONE;
}