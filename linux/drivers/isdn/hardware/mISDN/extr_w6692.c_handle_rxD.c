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
typedef  int u8 ;
struct TYPE_2__ {int /*<<< orphan*/ * rx_skb; int /*<<< orphan*/  err_rx; int /*<<< orphan*/  err_crc; } ;
struct w6692_hw {TYPE_1__ dch; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ReadW6692 (struct w6692_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  W6692_empty_Dfifo (struct w6692_hw*,int) ; 
 int /*<<< orphan*/  W_D_CMDR ; 
 int W_D_CMDR_RACK ; 
 int W_D_CMDR_RRST ; 
 int W_D_FIFO_THRESH ; 
 int /*<<< orphan*/  W_D_RBCL ; 
 int /*<<< orphan*/  W_D_RSTA ; 
 int W_D_RSTA_CRCE ; 
 int W_D_RSTA_RDOV ; 
 int W_D_RSTA_RMB ; 
 int /*<<< orphan*/  WriteW6692 (struct w6692_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  recv_Dchannel (TYPE_1__*) ; 

__attribute__((used)) static void
handle_rxD(struct w6692_hw *card) {
	u8	stat;
	int	count;

	stat = ReadW6692(card, W_D_RSTA);
	if (stat & (W_D_RSTA_RDOV | W_D_RSTA_CRCE | W_D_RSTA_RMB)) {
		if (stat & W_D_RSTA_RDOV) {
			pr_debug("%s: D-channel RDOV\n", card->name);
#ifdef ERROR_STATISTIC
			card->dch.err_rx++;
#endif
		}
		if (stat & W_D_RSTA_CRCE) {
			pr_debug("%s: D-channel CRC error\n", card->name);
#ifdef ERROR_STATISTIC
			card->dch.err_crc++;
#endif
		}
		if (stat & W_D_RSTA_RMB) {
			pr_debug("%s: D-channel ABORT\n", card->name);
#ifdef ERROR_STATISTIC
			card->dch.err_rx++;
#endif
		}
		dev_kfree_skb(card->dch.rx_skb);
		card->dch.rx_skb = NULL;
		WriteW6692(card, W_D_CMDR, W_D_CMDR_RACK | W_D_CMDR_RRST);
	} else {
		count = ReadW6692(card, W_D_RBCL) & (W_D_FIFO_THRESH - 1);
		if (count == 0)
			count = W_D_FIFO_THRESH;
		W6692_empty_Dfifo(card, count);
		recv_Dchannel(&card->dch);
	}
}