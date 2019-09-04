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
struct sudmac_chan {int dint_end_bit; } ;
struct shdma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SUDMAC_DINTSTS ; 
 int /*<<< orphan*/  sudmac_dma_halt (struct sudmac_chan*) ; 
 int sudmac_readl (struct sudmac_chan*,int /*<<< orphan*/ ) ; 
 struct sudmac_chan* to_chan (struct shdma_chan*) ; 

__attribute__((used)) static bool sudmac_chan_irq(struct shdma_chan *schan, int irq)
{
	struct sudmac_chan *sc = to_chan(schan);
	u32 dintsts = sudmac_readl(sc, SUDMAC_DINTSTS);

	if (!(dintsts & sc->dint_end_bit))
		return false;

	/* DMA stop */
	sudmac_dma_halt(sc);

	return true;
}