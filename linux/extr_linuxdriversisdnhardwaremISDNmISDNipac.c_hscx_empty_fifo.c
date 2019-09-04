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
typedef  int u8 ;
struct TYPE_4__ {int nr; int dropcnt; int debug; scalar_t__ rx_skb; int /*<<< orphan*/  Flags; } ;
struct hscx_hw {int /*<<< orphan*/  log; TYPE_1__* ip; TYPE_2__ bch; scalar_t__ off; } ;
struct TYPE_3__ {char* name; int type; int /*<<< orphan*/  hw; int /*<<< orphan*/  (* read_fifo ) (int /*<<< orphan*/ ,scalar_t__,int*,int) ;} ;

/* Variables and functions */
 int DEBUG_HW_BFIFO ; 
 int /*<<< orphan*/  DUMP_PREFIX_OFFSET ; 
 int /*<<< orphan*/  FLG_RX_OFF ; 
 scalar_t__ IPACX_RFIFOB ; 
 int IPAC_TYPE_IPACX ; 
 int bchannel_get_rxbuf (TYPE_2__*,int) ; 
 int /*<<< orphan*/  hscx_cmdr (struct hscx_hw*,int) ; 
 int /*<<< orphan*/  pr_debug (char*,char*,int,int) ; 
 int /*<<< orphan*/  pr_warning (char*,char*,int,int) ; 
 int /*<<< orphan*/  print_hex_dump_bytes (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int* skb_put (scalar_t__,int) ; 
 int /*<<< orphan*/  skb_trim (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int,char*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,scalar_t__,int*,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,scalar_t__,int*,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
hscx_empty_fifo(struct hscx_hw *hscx, u8 count)
{
	u8 *p;
	int maxlen;

	pr_debug("%s: B%1d %d\n", hscx->ip->name, hscx->bch.nr, count);
	if (test_bit(FLG_RX_OFF, &hscx->bch.Flags)) {
		hscx->bch.dropcnt += count;
		hscx_cmdr(hscx, 0x80); /* RMC */
		return;
	}
	maxlen = bchannel_get_rxbuf(&hscx->bch, count);
	if (maxlen < 0) {
		hscx_cmdr(hscx, 0x80); /* RMC */
		if (hscx->bch.rx_skb)
			skb_trim(hscx->bch.rx_skb, 0);
		pr_warning("%s.B%d: No bufferspace for %d bytes\n",
			   hscx->ip->name, hscx->bch.nr, count);
		return;
	}
	p = skb_put(hscx->bch.rx_skb, count);

	if (hscx->ip->type & IPAC_TYPE_IPACX)
		hscx->ip->read_fifo(hscx->ip->hw,
				    hscx->off + IPACX_RFIFOB, p, count);
	else
		hscx->ip->read_fifo(hscx->ip->hw,
				    hscx->off, p, count);

	hscx_cmdr(hscx, 0x80); /* RMC */

	if (hscx->bch.debug & DEBUG_HW_BFIFO) {
		snprintf(hscx->log, 64, "B%1d-recv %s %d ",
			 hscx->bch.nr, hscx->ip->name, count);
		print_hex_dump_bytes(hscx->log, DUMP_PREFIX_OFFSET, p, count);
	}
}