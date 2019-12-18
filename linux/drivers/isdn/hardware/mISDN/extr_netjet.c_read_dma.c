#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct TYPE_5__ {scalar_t__* start; scalar_t__ size; } ;
struct tiger_hw {char* name; int /*<<< orphan*/  log; TYPE_1__ recv; } ;
struct TYPE_7__ {int nr; int dropcnt; int maxlen; TYPE_2__* rx_skb; int /*<<< orphan*/  Flags; struct tiger_hw* hw; } ;
struct tiger_ch {scalar_t__ lastrx; TYPE_3__ bch; int /*<<< orphan*/  hrecv; scalar_t__* hrbuf; int /*<<< orphan*/  rxstate; } ;
struct TYPE_6__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int DEBUG_HW_BFIFO ; 
 int /*<<< orphan*/  DUMP_PREFIX_OFFSET ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FLG_RX_OFF ; 
 int /*<<< orphan*/  FLG_TRANSPARENT ; 
 int HDLC_CRC_ERROR ; 
 int HDLC_FRAMING_ERROR ; 
 int HDLC_LENGTH_ERROR ; 
 int /*<<< orphan*/  LOG_SIZE ; 
 int /*<<< orphan*/  RX_OVERRUN ; 
 int bchannel_get_rxbuf (TYPE_3__*,int) ; 
 int debug ; 
 int isdnhdlc_decode (int /*<<< orphan*/ *,scalar_t__*,int,int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_info (char*,char*,int,...) ; 
 int /*<<< orphan*/  pr_warning (char*,char*,int,int) ; 
 int /*<<< orphan*/  print_hex_dump_bytes (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  recv_Bchannel (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__* skb_put (TYPE_2__*,int) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,char*,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
read_dma(struct tiger_ch *bc, u32 idx, int cnt)
{
	struct tiger_hw *card = bc->bch.hw;
	int i, stat;
	u32 val;
	u8 *p, *pn;

	if (bc->lastrx == idx) {
		bc->rxstate |= RX_OVERRUN;
		pr_info("%s: B%1d overrun at idx %d\n", card->name,
			bc->bch.nr, idx);
	}
	bc->lastrx = idx;
	if (test_bit(FLG_RX_OFF, &bc->bch.Flags)) {
		bc->bch.dropcnt += cnt;
		return;
	}
	stat = bchannel_get_rxbuf(&bc->bch, cnt);
	/* only transparent use the count here, HDLC overun is detected later */
	if (stat == -ENOMEM) {
		pr_warning("%s.B%d: No memory for %d bytes\n",
			   card->name, bc->bch.nr, cnt);
		return;
	}
	if (test_bit(FLG_TRANSPARENT, &bc->bch.Flags))
		p = skb_put(bc->bch.rx_skb, cnt);
	else
		p = bc->hrbuf;

	for (i = 0; i < cnt; i++) {
		val = card->recv.start[idx++];
		if (bc->bch.nr & 2)
			val >>= 8;
		if (idx >= card->recv.size)
			idx = 0;
		p[i] = val & 0xff;
	}

	if (test_bit(FLG_TRANSPARENT, &bc->bch.Flags)) {
		recv_Bchannel(&bc->bch, 0, false);
		return;
	}

	pn = bc->hrbuf;
	while (cnt > 0) {
		stat = isdnhdlc_decode(&bc->hrecv, pn, cnt, &i,
				       bc->bch.rx_skb->data, bc->bch.maxlen);
		if (stat > 0) { /* valid frame received */
			p = skb_put(bc->bch.rx_skb, stat);
			if (debug & DEBUG_HW_BFIFO) {
				snprintf(card->log, LOG_SIZE,
					 "B%1d-recv %s %d ", bc->bch.nr,
					 card->name, stat);
				print_hex_dump_bytes(card->log,
						     DUMP_PREFIX_OFFSET, p,
						     stat);
			}
			recv_Bchannel(&bc->bch, 0, false);
			stat = bchannel_get_rxbuf(&bc->bch, bc->bch.maxlen);
			if (stat < 0) {
				pr_warning("%s.B%d: No memory for %d bytes\n",
					   card->name, bc->bch.nr, cnt);
				return;
			}
		} else if (stat == -HDLC_CRC_ERROR) {
			pr_info("%s: B%1d receive frame CRC error\n",
				card->name, bc->bch.nr);
		} else if (stat == -HDLC_FRAMING_ERROR) {
			pr_info("%s: B%1d receive framing error\n",
				card->name, bc->bch.nr);
		} else if (stat == -HDLC_LENGTH_ERROR) {
			pr_info("%s: B%1d receive frame too long (> %d)\n",
				card->name, bc->bch.nr, bc->bch.maxlen);
		}
		pn += i;
		cnt -= i;
	}
}