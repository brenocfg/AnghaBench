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
struct ef4_tx_queue {struct ef4_tx_buffer* buffer; } ;
struct ef4_tx_buffer {int dummy; } ;

/* Variables and functions */
 size_t ef4_tx_queue_get_insert_index (struct ef4_tx_queue const*) ; 

__attribute__((used)) static inline struct ef4_tx_buffer *
__ef4_tx_queue_get_insert_buffer(const struct ef4_tx_queue *tx_queue)
{
	return &tx_queue->buffer[ef4_tx_queue_get_insert_index(tx_queue)];
}