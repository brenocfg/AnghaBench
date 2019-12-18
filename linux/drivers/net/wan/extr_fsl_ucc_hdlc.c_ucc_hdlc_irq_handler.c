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
typedef  int u32 ;
struct ucc_tdm_info {int dummy; } ;
struct ucc_hdlc_private {int /*<<< orphan*/  napi; struct ucc_fast_private* uccf; struct ucc_tdm_info* ut_info; struct net_device* ndev; } ;
struct ucc_fast_private {int /*<<< orphan*/  p_uccm; int /*<<< orphan*/  p_ucce; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  rx_missed_errors; } ;
struct net_device {TYPE_1__ stats; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int UCCE_HDLC_RX_EVENTS ; 
 int UCCE_HDLC_TX_EVENTS ; 
 int UCC_HDLC_UCCE_BSY ; 
 int UCC_HDLC_UCCE_TXE ; 
 int /*<<< orphan*/  __napi_schedule (int /*<<< orphan*/ *) ; 
 int ioread32be (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite32be (int,int /*<<< orphan*/ ) ; 
 scalar_t__ napi_schedule_prep (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t ucc_hdlc_irq_handler(int irq, void *dev_id)
{
	struct ucc_hdlc_private *priv = (struct ucc_hdlc_private *)dev_id;
	struct net_device *dev = priv->ndev;
	struct ucc_fast_private *uccf;
	struct ucc_tdm_info *ut_info;
	u32 ucce;
	u32 uccm;

	ut_info = priv->ut_info;
	uccf = priv->uccf;

	ucce = ioread32be(uccf->p_ucce);
	uccm = ioread32be(uccf->p_uccm);
	ucce &= uccm;
	iowrite32be(ucce, uccf->p_ucce);
	if (!ucce)
		return IRQ_NONE;

	if ((ucce >> 16) & (UCCE_HDLC_RX_EVENTS | UCCE_HDLC_TX_EVENTS)) {
		if (napi_schedule_prep(&priv->napi)) {
			uccm &= ~((UCCE_HDLC_RX_EVENTS | UCCE_HDLC_TX_EVENTS)
				  << 16);
			iowrite32be(uccm, uccf->p_uccm);
			__napi_schedule(&priv->napi);
		}
	}

	/* Errors and other events */
	if (ucce >> 16 & UCC_HDLC_UCCE_BSY)
		dev->stats.rx_missed_errors++;
	if (ucce >> 16 & UCC_HDLC_UCCE_TXE)
		dev->stats.tx_errors++;

	return IRQ_HANDLED;
}