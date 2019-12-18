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
typedef  scalar_t__ u16 ;
struct TYPE_2__ {scalar_t__ head; scalar_t__ tail; scalar_t__ size; } ;
struct fm10k_mbx_info {scalar_t__ pulled; scalar_t__ tail_len; TYPE_1__ rx; scalar_t__ head_len; scalar_t__ pushed; int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/  tx; int /*<<< orphan*/  tail; int /*<<< orphan*/  mbx_hdr; scalar_t__ max_size; } ;

/* Variables and functions */
 scalar_t__ FM10K_MSG_HDR_FIELD_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HEAD ; 
 scalar_t__ fm10k_fifo_head_drop (int /*<<< orphan*/ *) ; 
 scalar_t__ fm10k_fifo_head_len (int /*<<< orphan*/ *) ; 
 scalar_t__ fm10k_mbx_index_len (struct fm10k_mbx_info*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fm10k_mbx_reset_work(struct fm10k_mbx_info *mbx)
{
	u16 len, head, ack;

	/* reset our outgoing max size back to Rx limits */
	mbx->max_size = mbx->rx.size - 1;

	/* update mbx->pulled to account for tail_len and ack */
	head = FM10K_MSG_HDR_FIELD_GET(mbx->mbx_hdr, HEAD);
	ack = fm10k_mbx_index_len(mbx, head, mbx->tail);
	mbx->pulled += mbx->tail_len - ack;

	/* now drop any messages which have started or finished transmitting */
	while (fm10k_fifo_head_len(&mbx->tx) && mbx->pulled) {
		len = fm10k_fifo_head_drop(&mbx->tx);
		mbx->tx_dropped++;
		if (mbx->pulled >= len)
			mbx->pulled -= len;
		else
			mbx->pulled = 0;
	}

	/* just do a quick resysnc to start of message */
	mbx->pushed = 0;
	mbx->pulled = 0;
	mbx->tail_len = 0;
	mbx->head_len = 0;
	mbx->rx.tail = 0;
	mbx->rx.head = 0;
}