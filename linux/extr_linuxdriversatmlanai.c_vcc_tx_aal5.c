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
struct sk_buff {int /*<<< orphan*/  len; } ;
struct TYPE_2__ {int /*<<< orphan*/  backlog; } ;
struct lanai_vcc {TYPE_1__ tx; int /*<<< orphan*/  vci; } ;
struct lanai_dev {int /*<<< orphan*/  backlog_vccs; } ;

/* Variables and functions */
 int /*<<< orphan*/  APRINTK (int,char*,int) ; 
 int /*<<< orphan*/  TXREADPTR_GET_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int aal5_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cardvcc_read (struct lanai_vcc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lanai_send_one_aal5 (struct lanai_dev*,struct lanai_vcc*,struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 scalar_t__ vcc_is_backlogged (struct lanai_vcc*) ; 
 int vcc_tx_space (struct lanai_vcc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcc_txreadptr ; 

__attribute__((used)) static void vcc_tx_aal5(struct lanai_dev *lanai, struct lanai_vcc *lvcc,
	struct sk_buff *skb)
{
	int space, n;
	if (vcc_is_backlogged(lvcc))		/* Already backlogged */
		goto queue_it;
	space = vcc_tx_space(lvcc,
		    TXREADPTR_GET_PTR(cardvcc_read(lvcc, vcc_txreadptr)));
	n = aal5_size(skb->len);
	APRINTK(n + 16 >= 64, "vcc_tx_aal5: n too small (%d)\n", n);
	if (space < n + 16) {			/* No space for this PDU */
		__set_bit(lvcc->vci, lanai->backlog_vccs);
	    queue_it:
		skb_queue_tail(&lvcc->tx.backlog, skb);
		return;
	}
	lanai_send_one_aal5(lanai, lvcc, skb, n);
}