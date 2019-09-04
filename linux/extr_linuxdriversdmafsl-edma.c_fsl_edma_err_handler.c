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
struct fsl_edma_engine {unsigned int n_chans; TYPE_1__* chans; scalar_t__ membase; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int idle; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_ERROR ; 
 scalar_t__ EDMA_CERR ; 
 int /*<<< orphan*/  EDMA_CERR_CERR (unsigned int) ; 
 scalar_t__ EDMA_ERR ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 unsigned int edma_readl (struct fsl_edma_engine*,scalar_t__) ; 
 int /*<<< orphan*/  edma_writeb (struct fsl_edma_engine*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  fsl_edma_disable_request (TYPE_1__*) ; 

__attribute__((used)) static irqreturn_t fsl_edma_err_handler(int irq, void *dev_id)
{
	struct fsl_edma_engine *fsl_edma = dev_id;
	unsigned int err, ch;

	err = edma_readl(fsl_edma, fsl_edma->membase + EDMA_ERR);
	if (!err)
		return IRQ_NONE;

	for (ch = 0; ch < fsl_edma->n_chans; ch++) {
		if (err & (0x1 << ch)) {
			fsl_edma_disable_request(&fsl_edma->chans[ch]);
			edma_writeb(fsl_edma, EDMA_CERR_CERR(ch),
				fsl_edma->membase + EDMA_CERR);
			fsl_edma->chans[ch].status = DMA_ERROR;
			fsl_edma->chans[ch].idle = true;
		}
	}
	return IRQ_HANDLED;
}