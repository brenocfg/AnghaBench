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
struct ef4_tx_queue {scalar_t__ insert_count; scalar_t__ write_count; } ;
struct ef4_tx_buffer {int dummy; } ;

/* Variables and functions */
 struct ef4_tx_buffer* __ef4_tx_queue_get_insert_buffer (struct ef4_tx_queue*) ; 
 int /*<<< orphan*/  ef4_dequeue_buffer (struct ef4_tx_queue*,struct ef4_tx_buffer*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ef4_enqueue_unwind(struct ef4_tx_queue *tx_queue)
{
	struct ef4_tx_buffer *buffer;

	/* Work backwards until we hit the original insert pointer value */
	while (tx_queue->insert_count != tx_queue->write_count) {
		--tx_queue->insert_count;
		buffer = __ef4_tx_queue_get_insert_buffer(tx_queue);
		ef4_dequeue_buffer(tx_queue, buffer, NULL, NULL);
	}
}