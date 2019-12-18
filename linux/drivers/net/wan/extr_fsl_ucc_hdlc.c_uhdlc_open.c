#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct ucc_tdm {int tdm_port; TYPE_3__* si_regs; } ;
struct ucc_hdlc_private {int hdlc_busy; int /*<<< orphan*/  napi; int /*<<< orphan*/  ndev; scalar_t__ tsa; int /*<<< orphan*/  uccf; TYPE_2__* ut_info; struct ucc_tdm* utdm; } ;
struct net_device {int dummy; } ;
struct TYPE_9__ {struct ucc_hdlc_private* priv; } ;
typedef  TYPE_4__ hdlc_device ;
struct TYPE_8__ {int siglmr1_h; } ;
struct TYPE_6__ {int /*<<< orphan*/  ucc_num; int /*<<< orphan*/  irq; } ;
struct TYPE_7__ {TYPE_1__ uf_info; } ;

/* Variables and functions */
 int COMM_DIR_RX ; 
 int COMM_DIR_TX ; 
 int ENODEV ; 
 int /*<<< orphan*/  QE_CR_PROTOCOL_UNSPECIFIED ; 
 int /*<<< orphan*/  QE_INIT_TX_RX ; 
 TYPE_4__* dev_to_hdlc (struct net_device*) ; 
 int /*<<< orphan*/  hdlc_open (struct net_device*) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_reset_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_device_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  qe_issue_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct ucc_hdlc_private*) ; 
 int /*<<< orphan*/  ucc_fast_enable (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ucc_fast_get_qe_cr_subblock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ucc_hdlc_irq_handler ; 

__attribute__((used)) static int uhdlc_open(struct net_device *dev)
{
	u32 cecr_subblock;
	hdlc_device *hdlc = dev_to_hdlc(dev);
	struct ucc_hdlc_private *priv = hdlc->priv;
	struct ucc_tdm *utdm = priv->utdm;

	if (priv->hdlc_busy != 1) {
		if (request_irq(priv->ut_info->uf_info.irq,
				ucc_hdlc_irq_handler, 0, "hdlc", priv))
			return -ENODEV;

		cecr_subblock = ucc_fast_get_qe_cr_subblock(
					priv->ut_info->uf_info.ucc_num);

		qe_issue_cmd(QE_INIT_TX_RX, cecr_subblock,
			     QE_CR_PROTOCOL_UNSPECIFIED, 0);

		ucc_fast_enable(priv->uccf, COMM_DIR_RX | COMM_DIR_TX);

		/* Enable the TDM port */
		if (priv->tsa)
			utdm->si_regs->siglmr1_h |= (0x1 << utdm->tdm_port);

		priv->hdlc_busy = 1;
		netif_device_attach(priv->ndev);
		napi_enable(&priv->napi);
		netdev_reset_queue(dev);
		netif_start_queue(dev);
		hdlc_open(dev);
	}

	return 0;
}