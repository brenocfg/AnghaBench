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
struct txx9dmac_hwdesc32 {int /*<<< orphan*/  CSR; int /*<<< orphan*/  CCR; int /*<<< orphan*/  DAIR; int /*<<< orphan*/  SAIR; int /*<<< orphan*/  CNTR; int /*<<< orphan*/  DAR; int /*<<< orphan*/  SAR; int /*<<< orphan*/  CHAR; } ;
struct txx9dmac_hwdesc {int /*<<< orphan*/  CSR; int /*<<< orphan*/  CCR; int /*<<< orphan*/  DAIR; int /*<<< orphan*/  SAIR; int /*<<< orphan*/  CNTR; int /*<<< orphan*/  DAR; int /*<<< orphan*/  SAR; scalar_t__ CHAR; } ;
struct txx9dmac_chan {int /*<<< orphan*/  chan; } ;

/* Variables and functions */
 int /*<<< orphan*/  chan2dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_crit (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_dmac64 (struct txx9dmac_chan*) ; 

__attribute__((used)) static void txx9dmac_dump_desc(struct txx9dmac_chan *dc,
			       struct txx9dmac_hwdesc *desc)
{
	if (is_dmac64(dc)) {
#ifdef TXX9_DMA_USE_SIMPLE_CHAIN
		dev_crit(chan2dev(&dc->chan),
			 "  desc: ch%#llx s%#llx d%#llx c%#x\n",
			 (u64)desc->CHAR, desc->SAR, desc->DAR, desc->CNTR);
#else
		dev_crit(chan2dev(&dc->chan),
			 "  desc: ch%#llx s%#llx d%#llx c%#x"
			 " si%#x di%#x cc%#x cs%#x\n",
			 (u64)desc->CHAR, desc->SAR, desc->DAR, desc->CNTR,
			 desc->SAIR, desc->DAIR, desc->CCR, desc->CSR);
#endif
	} else {
		struct txx9dmac_hwdesc32 *d = (struct txx9dmac_hwdesc32 *)desc;
#ifdef TXX9_DMA_USE_SIMPLE_CHAIN
		dev_crit(chan2dev(&dc->chan),
			 "  desc: ch%#x s%#x d%#x c%#x\n",
			 d->CHAR, d->SAR, d->DAR, d->CNTR);
#else
		dev_crit(chan2dev(&dc->chan),
			 "  desc: ch%#x s%#x d%#x c%#x"
			 " si%#x di%#x cc%#x cs%#x\n",
			 d->CHAR, d->SAR, d->DAR, d->CNTR,
			 d->SAIR, d->DAIR, d->CCR, d->CSR);
#endif
	}
}