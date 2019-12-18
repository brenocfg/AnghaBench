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
struct queue_entry {unsigned int entry_idx; } ;
struct data_queue {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  Q_INDEX_DMA_DONE ; 
 struct queue_entry* rt2x00queue_get_entry (struct data_queue*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int rt2800usb_get_dma_done(struct data_queue *queue)
{
	struct queue_entry *entry;

	entry = rt2x00queue_get_entry(queue, Q_INDEX_DMA_DONE);
	return entry->entry_idx;
}