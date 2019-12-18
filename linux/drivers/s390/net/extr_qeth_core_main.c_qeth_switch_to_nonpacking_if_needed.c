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
struct qeth_qdio_out_q {scalar_t__ do_pack; int /*<<< orphan*/  card; int /*<<< orphan*/  used_buffers; } ;

/* Variables and functions */
 int /*<<< orphan*/  QETH_CARD_TEXT (int /*<<< orphan*/ ,int,char*) ; 
 scalar_t__ QETH_LOW_WATERMARK_PACK ; 
 int /*<<< orphan*/  QETH_TXQ_STAT_INC (struct qeth_qdio_out_q*,int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  packing_mode_switch ; 
 int qeth_prep_flush_pack_buffer (struct qeth_qdio_out_q*) ; 

__attribute__((used)) static int qeth_switch_to_nonpacking_if_needed(struct qeth_qdio_out_q *queue)
{
	if (queue->do_pack) {
		if (atomic_read(&queue->used_buffers)
		    <= QETH_LOW_WATERMARK_PACK) {
			/* switch PACKING -> non-PACKING */
			QETH_CARD_TEXT(queue->card, 6, "pack->np");
			QETH_TXQ_STAT_INC(queue, packing_mode_switch);
			queue->do_pack = 0;
			return qeth_prep_flush_pack_buffer(queue);
		}
	}
	return 0;
}