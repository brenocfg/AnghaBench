#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct octnic_data_pkt {int /*<<< orphan*/  reqtype; int /*<<< orphan*/  q_no; int /*<<< orphan*/  cmd; } ;
struct octnet_buf_free_info {int /*<<< orphan*/  skb; struct octeon_soft_command* sc; struct lio* lio; } ;
struct TYPE_4__ {int /*<<< orphan*/  ih3; } ;
struct TYPE_6__ {TYPE_1__ cmd3; } ;
struct octeon_soft_command {TYPE_3__ cmd; int /*<<< orphan*/  iq_no; int /*<<< orphan*/  callback_arg; int /*<<< orphan*/  callback; } ;
struct octeon_instr_ih3 {scalar_t__ dlengsz; } ;
struct octeon_device {TYPE_2__* pci_dev; } ;
struct oct_timestamp_resp {int dummy; } ;
struct lio {int /*<<< orphan*/  netdev; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int IQ_SEND_FAILED ; 
 int /*<<< orphan*/  REQTYPE_NORESP_NET ; 
 int /*<<< orphan*/  REQTYPE_NORESP_NET_SG ; 
 int /*<<< orphan*/  REQTYPE_RESP_NET ; 
 int /*<<< orphan*/  REQTYPE_RESP_NET_SG ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  handle_timestamp ; 
 int /*<<< orphan*/  netif_info (struct lio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 struct octeon_soft_command* octeon_alloc_soft_command_resp (struct octeon_device*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  octeon_free_soft_command (struct octeon_device*,struct octeon_soft_command*) ; 
 int octeon_send_command (struct octeon_device*,int /*<<< orphan*/ ,int,TYPE_3__*,struct octeon_soft_command*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tx_queued ; 

__attribute__((used)) static int send_nic_timestamp_pkt(struct octeon_device *oct,
				  struct octnic_data_pkt *ndata,
				  struct octnet_buf_free_info *finfo,
				  int xmit_more)
{
	struct octeon_soft_command *sc;
	int ring_doorbell;
	struct lio *lio;
	int retval;
	u32 len;

	lio = finfo->lio;

	sc = octeon_alloc_soft_command_resp(oct, &ndata->cmd,
					    sizeof(struct oct_timestamp_resp));
	finfo->sc = sc;

	if (!sc) {
		dev_err(&oct->pci_dev->dev, "No memory for timestamped data packet\n");
		return IQ_SEND_FAILED;
	}

	if (ndata->reqtype == REQTYPE_NORESP_NET)
		ndata->reqtype = REQTYPE_RESP_NET;
	else if (ndata->reqtype == REQTYPE_NORESP_NET_SG)
		ndata->reqtype = REQTYPE_RESP_NET_SG;

	sc->callback = handle_timestamp;
	sc->callback_arg = finfo->skb;
	sc->iq_no = ndata->q_no;

	len = (u32)((struct octeon_instr_ih3 *)(&sc->cmd.cmd3.ih3))->dlengsz;

	ring_doorbell = !xmit_more;

	retval = octeon_send_command(oct, sc->iq_no, ring_doorbell, &sc->cmd,
				     sc, len, ndata->reqtype);

	if (retval == IQ_SEND_FAILED) {
		dev_err(&oct->pci_dev->dev, "timestamp data packet failed status: %x\n",
			retval);
		octeon_free_soft_command(oct, sc);
	} else {
		netif_info(lio, tx_queued, lio->netdev, "Queued timestamp packet\n");
	}

	return retval;
}