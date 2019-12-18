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
typedef  size_t uint ;
typedef  scalar_t__ u16 ;
struct sk_buff {int priority; scalar_t__ cb; int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct device {int dummy; } ;
struct brcmf_sdio_dev {scalar_t__ state; struct brcmf_sdio* bus; } ;
struct TYPE_4__ {int /*<<< orphan*/  fcqueued; } ;
struct brcmf_sdio {int txoff; int /*<<< orphan*/  txq; int /*<<< orphan*/  txq_lock; int /*<<< orphan*/  tx_hdrlen; TYPE_2__ sdcnt; } ;
struct TYPE_3__ {struct brcmf_sdio_dev* sdio; } ;
struct brcmf_bus {TYPE_1__ bus_priv; } ;

/* Variables and functions */
 scalar_t__ BRCMF_SDIOD_DATA ; 
 int EBADE ; 
 int EIO ; 
 int ENOSR ; 
 int PRIOMASK ; 
 int /*<<< orphan*/  TRACE ; 
 scalar_t__ TXHI ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  brcmf_err (char*) ; 
 int /*<<< orphan*/  brcmf_proto_bcdc_txflowblock (struct device*,int) ; 
 int /*<<< orphan*/  brcmf_sdio_prec_enq (int /*<<< orphan*/ *,struct sk_buff*,size_t) ; 
 int /*<<< orphan*/  brcmf_sdio_trigger_dpc (struct brcmf_sdio*) ; 
 struct brcmf_bus* dev_get_drvdata (struct device*) ; 
 scalar_t__ pktq_len (int /*<<< orphan*/ *) ; 
 scalar_t__ pktq_plen (int /*<<< orphan*/ *,size_t) ; 
 size_t prio2prec (int) ; 
 scalar_t__* qcount ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int brcmf_sdio_bus_txdata(struct device *dev, struct sk_buff *pkt)
{
	int ret = -EBADE;
	uint prec;
	struct brcmf_bus *bus_if = dev_get_drvdata(dev);
	struct brcmf_sdio_dev *sdiodev = bus_if->bus_priv.sdio;
	struct brcmf_sdio *bus = sdiodev->bus;

	brcmf_dbg(TRACE, "Enter: pkt: data %p len %d\n", pkt->data, pkt->len);
	if (sdiodev->state != BRCMF_SDIOD_DATA)
		return -EIO;

	/* Add space for the header */
	skb_push(pkt, bus->tx_hdrlen);
	/* precondition: IS_ALIGNED((unsigned long)(pkt->data), 2) */

	prec = prio2prec((pkt->priority & PRIOMASK));

	/* Check for existing queue, current flow-control,
			 pending event, or pending clock */
	brcmf_dbg(TRACE, "deferring pktq len %d\n", pktq_len(&bus->txq));
	bus->sdcnt.fcqueued++;

	/* Priority based enq */
	spin_lock_bh(&bus->txq_lock);
	/* reset bus_flags in packet cb */
	*(u16 *)(pkt->cb) = 0;
	if (!brcmf_sdio_prec_enq(&bus->txq, pkt, prec)) {
		skb_pull(pkt, bus->tx_hdrlen);
		brcmf_err("out of bus->txq !!!\n");
		ret = -ENOSR;
	} else {
		ret = 0;
	}

	if (pktq_len(&bus->txq) >= TXHI) {
		bus->txoff = true;
		brcmf_proto_bcdc_txflowblock(dev, true);
	}
	spin_unlock_bh(&bus->txq_lock);

#ifdef DEBUG
	if (pktq_plen(&bus->txq, prec) > qcount[prec])
		qcount[prec] = pktq_plen(&bus->txq, prec);
#endif

	brcmf_sdio_trigger_dpc(bus);
	return ret;
}