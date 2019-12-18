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
struct ravb_private {scalar_t__ chip_id; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCC ; 
 int /*<<< orphan*/  CCC_OPC ; 
 int /*<<< orphan*/  CCC_OPC_OPERATION ; 
 int /*<<< orphan*/  CIE ; 
 int CIE_CL0M ; 
 int CIE_CRIE ; 
 int CIE_CTIE ; 
 int /*<<< orphan*/  DIL ; 
 int /*<<< orphan*/  RAVB_BE ; 
 int /*<<< orphan*/  RAVB_NC ; 
 scalar_t__ RCAR_GEN3 ; 
 int /*<<< orphan*/  RCR ; 
 int RCR_EFFS ; 
 int RCR_ENCF ; 
 int RCR_ESF ; 
 int RCR_ETS0 ; 
 int /*<<< orphan*/  RIC0 ; 
 int RIC0_FRE0 ; 
 int RIC0_FRE1 ; 
 int /*<<< orphan*/  RIC1 ; 
 int /*<<< orphan*/  RIC2 ; 
 int RIC2_QFE0 ; 
 int RIC2_QFE1 ; 
 int RIC2_RFFE ; 
 int /*<<< orphan*/  TCCR ; 
 int TCCR_TFEN ; 
 int /*<<< orphan*/  TGC ; 
 int TGC_TQP_AVBMODE1 ; 
 int /*<<< orphan*/  TIC ; 
 int TIC_FTE0 ; 
 int TIC_FTE1 ; 
 int TIC_TFUE ; 
 struct ravb_private* netdev_priv (struct net_device*) ; 
 int ravb_config (struct net_device*) ; 
 int /*<<< orphan*/  ravb_modify (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ravb_ring_format (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ravb_ring_free (struct net_device*,int /*<<< orphan*/ ) ; 
 int ravb_ring_init (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ravb_write (struct net_device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ravb_dmac_init(struct net_device *ndev)
{
	struct ravb_private *priv = netdev_priv(ndev);
	int error;

	/* Set CONFIG mode */
	error = ravb_config(ndev);
	if (error)
		return error;

	error = ravb_ring_init(ndev, RAVB_BE);
	if (error)
		return error;
	error = ravb_ring_init(ndev, RAVB_NC);
	if (error) {
		ravb_ring_free(ndev, RAVB_BE);
		return error;
	}

	/* Descriptor format */
	ravb_ring_format(ndev, RAVB_BE);
	ravb_ring_format(ndev, RAVB_NC);

	/* Set AVB RX */
	ravb_write(ndev,
		   RCR_EFFS | RCR_ENCF | RCR_ETS0 | RCR_ESF | 0x18000000, RCR);

	/* Set FIFO size */
	ravb_write(ndev, TGC_TQP_AVBMODE1 | 0x00112200, TGC);

	/* Timestamp enable */
	ravb_write(ndev, TCCR_TFEN, TCCR);

	/* Interrupt init: */
	if (priv->chip_id == RCAR_GEN3) {
		/* Clear DIL.DPLx */
		ravb_write(ndev, 0, DIL);
		/* Set queue specific interrupt */
		ravb_write(ndev, CIE_CRIE | CIE_CTIE | CIE_CL0M, CIE);
	}
	/* Frame receive */
	ravb_write(ndev, RIC0_FRE0 | RIC0_FRE1, RIC0);
	/* Disable FIFO full warning */
	ravb_write(ndev, 0, RIC1);
	/* Receive FIFO full error, descriptor empty */
	ravb_write(ndev, RIC2_QFE0 | RIC2_QFE1 | RIC2_RFFE, RIC2);
	/* Frame transmitted, timestamp FIFO updated */
	ravb_write(ndev, TIC_FTE0 | TIC_FTE1 | TIC_TFUE, TIC);

	/* Setting the control will start the AVB-DMAC process. */
	ravb_modify(ndev, CCC, CCC_OPC, CCC_OPC_OPERATION);

	return 0;
}