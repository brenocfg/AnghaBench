#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct dchannel {int maxlen; TYPE_1__* rx_skb; } ;
struct w6692_hw {char* name; int /*<<< orphan*/  log; scalar_t__ addr; struct dchannel dch; } ;
struct TYPE_3__ {int len; } ;

/* Variables and functions */
 int DEBUG_HW_DFIFO ; 
 int /*<<< orphan*/  DUMP_PREFIX_OFFSET ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  W_D_CMDR ; 
 int /*<<< orphan*/  W_D_CMDR_RACK ; 
 scalar_t__ W_D_RFIFO ; 
 int /*<<< orphan*/  WriteW6692 (struct w6692_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int debug ; 
 int /*<<< orphan*/  insb (scalar_t__,int /*<<< orphan*/ *,int) ; 
 TYPE_1__* mI_alloc_skb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,char*,int) ; 
 int /*<<< orphan*/  pr_info (char*,char*) ; 
 int /*<<< orphan*/  print_hex_dump_bytes (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * skb_put (TYPE_1__*,int) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,int) ; 

__attribute__((used)) static void
W6692_empty_Dfifo(struct w6692_hw *card, int count)
{
	struct dchannel *dch = &card->dch;
	u8 *ptr;

	pr_debug("%s: empty_Dfifo %d\n", card->name, count);
	if (!dch->rx_skb) {
		dch->rx_skb = mI_alloc_skb(card->dch.maxlen, GFP_ATOMIC);
		if (!dch->rx_skb) {
			pr_info("%s: D receive out of memory\n", card->name);
			WriteW6692(card, W_D_CMDR, W_D_CMDR_RACK);
			return;
		}
	}
	if ((dch->rx_skb->len + count) >= dch->maxlen) {
		pr_debug("%s: empty_Dfifo overrun %d\n", card->name,
			 dch->rx_skb->len + count);
		WriteW6692(card, W_D_CMDR, W_D_CMDR_RACK);
		return;
	}
	ptr = skb_put(dch->rx_skb, count);
	insb(card->addr + W_D_RFIFO, ptr, count);
	WriteW6692(card, W_D_CMDR, W_D_CMDR_RACK);
	if (debug & DEBUG_HW_DFIFO) {
		snprintf(card->log, 63, "D-recv %s %d ",
			 card->name, count);
		print_hex_dump_bytes(card->log, DUMP_PREFIX_OFFSET, ptr, count);
	}
}