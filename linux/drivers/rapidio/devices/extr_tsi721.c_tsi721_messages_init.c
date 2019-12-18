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
struct tsi721_device {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ TSI721_IBDMAC_INT (int) ; 
 int /*<<< orphan*/  TSI721_IBDMAC_INT_MASK ; 
 scalar_t__ TSI721_IBDMAC_STS (int) ; 
 int TSI721_IMSG_CHNUM ; 
 scalar_t__ TSI721_RETRY_GEN_CNT ; 
 scalar_t__ TSI721_RETRY_RX_CNT ; 
 scalar_t__ TSI721_RQRPTO ; 
 int /*<<< orphan*/  TSI721_RQRPTO_VAL ; 
 scalar_t__ TSI721_SMSG_ECC_COR_LOG (int) ; 
 int /*<<< orphan*/  TSI721_SMSG_ECC_COR_LOG_MASK ; 
 scalar_t__ TSI721_SMSG_ECC_LOG ; 
 scalar_t__ TSI721_SMSG_ECC_NCOR (int) ; 
 int /*<<< orphan*/  TSI721_SMSG_ECC_NCOR_MASK ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int tsi721_messages_init(struct tsi721_device *priv)
{
	int	ch;

	iowrite32(0, priv->regs + TSI721_SMSG_ECC_LOG);
	iowrite32(0, priv->regs + TSI721_RETRY_GEN_CNT);
	iowrite32(0, priv->regs + TSI721_RETRY_RX_CNT);

	/* Set SRIO Message Request/Response Timeout */
	iowrite32(TSI721_RQRPTO_VAL, priv->regs + TSI721_RQRPTO);

	/* Initialize Inbound Messaging Engine Registers */
	for (ch = 0; ch < TSI721_IMSG_CHNUM; ch++) {
		/* Clear interrupt bits */
		iowrite32(TSI721_IBDMAC_INT_MASK,
			priv->regs + TSI721_IBDMAC_INT(ch));
		/* Clear Status */
		iowrite32(0, priv->regs + TSI721_IBDMAC_STS(ch));

		iowrite32(TSI721_SMSG_ECC_COR_LOG_MASK,
				priv->regs + TSI721_SMSG_ECC_COR_LOG(ch));
		iowrite32(TSI721_SMSG_ECC_NCOR_MASK,
				priv->regs + TSI721_SMSG_ECC_NCOR(ch));
	}

	return 0;
}