#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct tty_struct {int dummy; } ;
struct r3964_info {size_t tx_position; int flags; scalar_t__ bcc; int /*<<< orphan*/  tmr; int /*<<< orphan*/  state; struct r3964_block_header* tx_first; struct tty_struct* tty; } ;
struct r3964_block_header {size_t length; scalar_t__* data; } ;

/* Variables and functions */
 scalar_t__ DLE ; 
 scalar_t__ ETX ; 
 int R3964_BCC ; 
 scalar_t__ R3964_TO_QVZ ; 
 int /*<<< orphan*/  R3964_WAIT_FOR_TX_ACK ; 
 int /*<<< orphan*/  TRACE_PS (char*,struct r3964_block_header*,int,size_t) ; 
 int /*<<< orphan*/  flush (struct r3964_info*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  put_char (struct r3964_info*,scalar_t__) ; 
 int tty_write_room (struct tty_struct*) ; 

__attribute__((used)) static void transmit_block(struct r3964_info *pInfo)
{
	struct tty_struct *tty = pInfo->tty;
	struct r3964_block_header *pBlock = pInfo->tx_first;
	int room = 0;

	if (tty == NULL || pBlock == NULL) {
		return;
	}

	room = tty_write_room(tty);

	TRACE_PS("transmit_block %p, room %d, length %d",
		 pBlock, room, pBlock->length);

	while (pInfo->tx_position < pBlock->length) {
		if (room < 2)
			break;

		if (pBlock->data[pInfo->tx_position] == DLE) {
			/* send additional DLE char: */
			put_char(pInfo, DLE);
		}
		put_char(pInfo, pBlock->data[pInfo->tx_position++]);

		room--;
	}

	if ((pInfo->tx_position == pBlock->length) && (room >= 3)) {
		put_char(pInfo, DLE);
		put_char(pInfo, ETX);
		if (pInfo->flags & R3964_BCC) {
			put_char(pInfo, pInfo->bcc);
		}
		pInfo->state = R3964_WAIT_FOR_TX_ACK;
		mod_timer(&pInfo->tmr, jiffies + R3964_TO_QVZ);
	}
	flush(pInfo);
}