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
typedef  int /*<<< orphan*/  u_char ;
struct isac {int tx_cnt; int /*<<< orphan*/  (* write_isac ) (struct isac*,int /*<<< orphan*/ ,unsigned char) ;int /*<<< orphan*/  (* write_isac_fifo ) (struct isac*,int /*<<< orphan*/ *,int) ;TYPE_1__* tx_skb; } ;
struct TYPE_2__ {int len; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DBG (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  DBG_IRQ ; 
 int /*<<< orphan*/  DBG_PACKET (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  DBG_XFIFO ; 
 int /*<<< orphan*/  ISAC_CMDR ; 
 unsigned char ISAC_CMDR_XME ; 
 unsigned char ISAC_CMDR_XTF ; 
 int /*<<< orphan*/  skb_pull (TYPE_1__*,int) ; 
 int /*<<< orphan*/  stub1 (struct isac*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub2 (struct isac*,int /*<<< orphan*/ ,unsigned char) ; 

__attribute__((used)) static void isac_fill_fifo(struct isac *isac)
{
	// this also works for isacsx, since
	// CMDR(D) register works the same

	int count;
	unsigned char cmd;
	u_char *ptr;

	BUG_ON(!isac->tx_skb);

	count = isac->tx_skb->len;
	BUG_ON(count <= 0);

	DBG(DBG_IRQ, "count %d", count);

	if (count > 0x20) {
		count = 0x20;
		cmd = ISAC_CMDR_XTF;
	} else {
		cmd = ISAC_CMDR_XTF | ISAC_CMDR_XME;
	}

	ptr = isac->tx_skb->data;
	skb_pull(isac->tx_skb, count);
	isac->tx_cnt += count;
	DBG_PACKET(DBG_XFIFO, ptr, count);
	isac->write_isac_fifo(isac, ptr, count);
	isac->write_isac(isac, ISAC_CMDR, cmd);
}