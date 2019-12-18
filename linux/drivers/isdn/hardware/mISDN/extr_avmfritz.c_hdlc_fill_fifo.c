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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct TYPE_5__ {int xml; int /*<<< orphan*/  cmd; } ;
struct TYPE_6__ {TYPE_2__ sr; } ;
struct hdlc_hw {TYPE_3__ ctrl; } ;
struct fritzcard {scalar_t__ type; char* name; int /*<<< orphan*/  log; scalar_t__ addr; struct hdlc_hw* hdlc; } ;
struct bchannel {int nr; int tx_idx; TYPE_1__* tx_skb; int /*<<< orphan*/  Flags; int /*<<< orphan*/ * fill; struct fritzcard* hw; } ;
struct TYPE_4__ {int len; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 scalar_t__ AVM_FRITZ_PCIV2 ; 
 scalar_t__ AVM_HDLC_FIFO_1 ; 
 scalar_t__ AVM_HDLC_FIFO_2 ; 
 scalar_t__ CHIP_WINDOW ; 
 int DEBUG_HW_BFIFO ; 
 int /*<<< orphan*/  DUMP_PREFIX_OFFSET ; 
 int /*<<< orphan*/  FLG_HDLC ; 
 int /*<<< orphan*/  FLG_TX_EMPTY ; 
 int /*<<< orphan*/  HDLC_CMD_XME ; 
 int HDLC_FIFO_SIZE_V1 ; 
 int HDLC_FIFO_SIZE_V2 ; 
 int /*<<< orphan*/  LOG_SIZE ; 
 int /*<<< orphan*/  __write_ctrl_pci (struct fritzcard*,struct hdlc_hw*,int) ; 
 int /*<<< orphan*/  __write_ctrl_pciv2 (struct fritzcard*,struct hdlc_hw*,int) ; 
 scalar_t__ cpu_to_le32 (scalar_t__) ; 
 int debug ; 
 scalar_t__ get_unaligned (scalar_t__*) ; 
 int /*<<< orphan*/  outl (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  pr_debug (char*,char*,int,int,...) ; 
 int /*<<< orphan*/  print_hex_dump_bytes (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,char*,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
hdlc_fill_fifo(struct bchannel *bch)
{
	struct fritzcard *fc = bch->hw;
	struct hdlc_hw *hdlc;
	int count, fs, cnt = 0, idx;
	bool fillempty = false;
	u8 *p;
	u32 *ptr, val, addr;

	idx = (bch->nr - 1) & 1;
	hdlc = &fc->hdlc[idx];
	fs = (fc->type == AVM_FRITZ_PCIV2) ?
		HDLC_FIFO_SIZE_V2 : HDLC_FIFO_SIZE_V1;
	if (!bch->tx_skb) {
		if (!test_bit(FLG_TX_EMPTY, &bch->Flags))
			return;
		count = fs;
		p = bch->fill;
		fillempty = true;
	} else {
		count = bch->tx_skb->len - bch->tx_idx;
		if (count <= 0)
			return;
		p = bch->tx_skb->data + bch->tx_idx;
	}
	hdlc->ctrl.sr.cmd &= ~HDLC_CMD_XME;
	if (count > fs) {
		count = fs;
	} else {
		if (test_bit(FLG_HDLC, &bch->Flags))
			hdlc->ctrl.sr.cmd |= HDLC_CMD_XME;
	}
	ptr = (u32 *)p;
	if (!fillempty) {
		pr_debug("%s.B%d: %d/%d/%d", fc->name, bch->nr, count,
			 bch->tx_idx, bch->tx_skb->len);
		bch->tx_idx += count;
	} else {
		pr_debug("%s.B%d: fillempty %d\n", fc->name, bch->nr, count);
	}
	hdlc->ctrl.sr.xml = ((count == fs) ? 0 : count);
	if (fc->type == AVM_FRITZ_PCIV2) {
		__write_ctrl_pciv2(fc, hdlc, bch->nr);
		addr = fc->addr + (bch->nr == 2 ?
				   AVM_HDLC_FIFO_2 : AVM_HDLC_FIFO_1);
	} else {
		__write_ctrl_pci(fc, hdlc, bch->nr);
		addr = fc->addr + CHIP_WINDOW;
	}
	if (fillempty) {
		while (cnt < count) {
			/* all bytes the same - no worry about endian */
			outl(*ptr, addr);
			cnt += 4;
		}
	} else {
		while (cnt < count) {
			val = get_unaligned(ptr);
			outl(cpu_to_le32(val), addr);
			ptr++;
			cnt += 4;
		}
	}
	if ((debug & DEBUG_HW_BFIFO) && !fillempty) {
		snprintf(fc->log, LOG_SIZE, "B%1d-send %s %d ",
			 bch->nr, fc->name, count);
		print_hex_dump_bytes(fc->log, DUMP_PREFIX_OFFSET, p, count);
	}
}