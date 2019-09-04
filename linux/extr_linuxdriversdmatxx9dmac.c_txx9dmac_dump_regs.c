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
struct txx9dmac_chan {int /*<<< orphan*/  chan; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCR ; 
 int /*<<< orphan*/  CHAR ; 
 int /*<<< orphan*/  CNTR ; 
 int /*<<< orphan*/  CSR ; 
 int /*<<< orphan*/  DAIR ; 
 int /*<<< orphan*/  DAR ; 
 int /*<<< orphan*/  SAIR ; 
 int /*<<< orphan*/  SAR ; 
 int /*<<< orphan*/  chan2dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  channel32_readl (struct txx9dmac_chan*,int /*<<< orphan*/ ) ; 
 scalar_t__ channel64_read_CHAR (struct txx9dmac_chan*) ; 
 int /*<<< orphan*/  channel64_readl (struct txx9dmac_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  channel64_readq (struct txx9dmac_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_dmac64 (struct txx9dmac_chan*) ; 

__attribute__((used)) static void txx9dmac_dump_regs(struct txx9dmac_chan *dc)
{
	if (is_dmac64(dc))
		dev_err(chan2dev(&dc->chan),
			"  CHAR: %#llx SAR: %#llx DAR: %#llx CNTR: %#x"
			" SAIR: %#x DAIR: %#x CCR: %#x CSR: %#x\n",
			(u64)channel64_read_CHAR(dc),
			channel64_readq(dc, SAR),
			channel64_readq(dc, DAR),
			channel64_readl(dc, CNTR),
			channel64_readl(dc, SAIR),
			channel64_readl(dc, DAIR),
			channel64_readl(dc, CCR),
			channel64_readl(dc, CSR));
	else
		dev_err(chan2dev(&dc->chan),
			"  CHAR: %#x SAR: %#x DAR: %#x CNTR: %#x"
			" SAIR: %#x DAIR: %#x CCR: %#x CSR: %#x\n",
			channel32_readl(dc, CHAR),
			channel32_readl(dc, SAR),
			channel32_readl(dc, DAR),
			channel32_readl(dc, CNTR),
			channel32_readl(dc, SAIR),
			channel32_readl(dc, DAIR),
			channel32_readl(dc, CCR),
			channel32_readl(dc, CSR));
}