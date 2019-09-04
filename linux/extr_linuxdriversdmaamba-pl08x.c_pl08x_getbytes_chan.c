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
typedef  size_t u32 ;
struct pl08x_txd {size_t* llis_va; size_t llis_bus; } ;
struct pl08x_phy_chan {int /*<<< orphan*/  reg_lli; } ;
struct pl08x_driver_data {size_t lli_words; } ;
struct pl08x_dma_chan {struct pl08x_txd* at; struct pl08x_phy_chan* phychan; struct pl08x_driver_data* host; } ;
typedef  size_t dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 size_t MAX_NUM_TSFR_LLIS ; 
 size_t PL080_LLI_LLI ; 
 size_t PL080_LLI_LM_AHB2 ; 
 scalar_t__ get_bytes_in_lli (struct pl08x_phy_chan*,size_t const*) ; 
 size_t get_bytes_in_phy_channel (struct pl08x_phy_chan*) ; 
 size_t readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 pl08x_getbytes_chan(struct pl08x_dma_chan *plchan)
{
	struct pl08x_driver_data *pl08x = plchan->host;
	const u32 *llis_va, *llis_va_limit;
	struct pl08x_phy_chan *ch;
	dma_addr_t llis_bus;
	struct pl08x_txd *txd;
	u32 llis_max_words;
	size_t bytes;
	u32 clli;

	ch = plchan->phychan;
	txd = plchan->at;

	if (!ch || !txd)
		return 0;

	/*
	 * Follow the LLIs to get the number of remaining
	 * bytes in the currently active transaction.
	 */
	clli = readl(ch->reg_lli) & ~PL080_LLI_LM_AHB2;

	/* First get the remaining bytes in the active transfer */
	bytes = get_bytes_in_phy_channel(ch);

	if (!clli)
		return bytes;

	llis_va = txd->llis_va;
	llis_bus = txd->llis_bus;

	llis_max_words = pl08x->lli_words * MAX_NUM_TSFR_LLIS;
	BUG_ON(clli < llis_bus || clli >= llis_bus +
						sizeof(u32) * llis_max_words);

	/*
	 * Locate the next LLI - as this is an array,
	 * it's simple maths to find.
	 */
	llis_va += (clli - llis_bus) / sizeof(u32);

	llis_va_limit = llis_va + llis_max_words;

	for (; llis_va < llis_va_limit; llis_va += pl08x->lli_words) {
		bytes += get_bytes_in_lli(ch, llis_va);

		/*
		 * A LLI pointer going backward terminates the LLI list
		 */
		if (llis_va[PL080_LLI_LLI] <= clli)
			break;
	}

	return bytes;
}