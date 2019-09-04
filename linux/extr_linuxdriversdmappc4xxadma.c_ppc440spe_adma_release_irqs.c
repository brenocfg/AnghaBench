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
typedef  int u32 ;
struct ppc440spe_adma_device {scalar_t__ id; scalar_t__ irq; scalar_t__ err_irq; TYPE_2__* i2o_reg; TYPE_1__* xor_reg; } ;
struct ppc440spe_adma_chan {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  iopim; } ;
struct TYPE_3__ {int /*<<< orphan*/  ier; } ;

/* Variables and functions */
 int I2O_IOPIM_P0EM ; 
 int I2O_IOPIM_P0SNE ; 
 int I2O_IOPIM_P1EM ; 
 int I2O_IOPIM_P1SNE ; 
 scalar_t__ PPC440SPE_DMA0_ID ; 
 scalar_t__ PPC440SPE_XOR_ID ; 
 int XOR_IE_CBCIE_BIT ; 
 int XOR_IE_ICBIE_BIT ; 
 int XOR_IE_ICIE_BIT ; 
 int XOR_IE_RPTIE_BIT ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct ppc440spe_adma_chan*) ; 
 int ioread32 (int /*<<< orphan*/ *) ; 
 int ioread32be (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iounmap (TYPE_2__*) ; 
 int /*<<< orphan*/  iowrite32 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite32be (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_dispose_mapping (scalar_t__) ; 
 int /*<<< orphan*/  ppc440spe_adma_err_irq_ref ; 

__attribute__((used)) static void ppc440spe_adma_release_irqs(struct ppc440spe_adma_device *adev,
					struct ppc440spe_adma_chan *chan)
{
	u32 mask, disable;

	if (adev->id == PPC440SPE_XOR_ID) {
		/* disable XOR engine interrupts */
		mask = ioread32be(&adev->xor_reg->ier);
		mask &= ~(XOR_IE_CBCIE_BIT | XOR_IE_ICBIE_BIT |
			  XOR_IE_ICIE_BIT | XOR_IE_RPTIE_BIT);
		iowrite32be(mask, &adev->xor_reg->ier);
	} else {
		/* disable DMAx engine interrupts */
		disable = (adev->id == PPC440SPE_DMA0_ID) ?
			  (I2O_IOPIM_P0SNE | I2O_IOPIM_P0EM) :
			  (I2O_IOPIM_P1SNE | I2O_IOPIM_P1EM);
		mask = ioread32(&adev->i2o_reg->iopim) | disable;
		iowrite32(mask, &adev->i2o_reg->iopim);
	}
	free_irq(adev->irq, chan);
	irq_dispose_mapping(adev->irq);
	if (adev->err_irq > 0) {
		free_irq(adev->err_irq, chan);
		if (atomic_dec_and_test(&ppc440spe_adma_err_irq_ref)) {
			irq_dispose_mapping(adev->err_irq);
			iounmap(adev->i2o_reg);
		}
	}
}