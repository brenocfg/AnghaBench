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
struct xor_regs {int /*<<< orphan*/  crsr; } ;
struct ppc440spe_adma_chan {TYPE_1__* device; } ;
struct TYPE_2__ {int id; struct xor_regs* xor_reg; } ;

/* Variables and functions */
#define  PPC440SPE_DMA0_ID 130 
#define  PPC440SPE_DMA1_ID 129 
#define  PPC440SPE_XOR_ID 128 
 int XOR_CRSR_64BA_BIT ; 
 int XOR_CRSR_XAE_BIT ; 
 int /*<<< orphan*/  iowrite32be (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ppc440spe_chan_run(struct ppc440spe_adma_chan *chan)
{
	struct xor_regs *xor_reg;

	switch (chan->device->id) {
	case PPC440SPE_DMA0_ID:
	case PPC440SPE_DMA1_ID:
		/* DMAs are always enabled, do nothing */
		break;
	case PPC440SPE_XOR_ID:
		/* drain write buffer */
		xor_reg = chan->device->xor_reg;

		/* fetch descriptor pointed to in <link> */
		iowrite32be(XOR_CRSR_64BA_BIT | XOR_CRSR_XAE_BIT,
			    &xor_reg->crsr);
		break;
	}
}