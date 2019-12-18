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
struct queue_entry {unsigned int entry_idx; int /*<<< orphan*/  priv_data; int /*<<< orphan*/ * skb; struct data_queue* queue; scalar_t__ flags; } ;
struct data_queue {int priv_size; unsigned int limit; struct queue_entry* entries; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  QUEUE_ENTRY_PRIV_OFFSET (struct queue_entry*,unsigned int,unsigned int,int,int) ; 
 struct queue_entry* kcalloc (unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00queue_reset (struct data_queue*) ; 

__attribute__((used)) static int rt2x00queue_alloc_entries(struct data_queue *queue)
{
	struct queue_entry *entries;
	unsigned int entry_size;
	unsigned int i;

	rt2x00queue_reset(queue);

	/*
	 * Allocate all queue entries.
	 */
	entry_size = sizeof(*entries) + queue->priv_size;
	entries = kcalloc(queue->limit, entry_size, GFP_KERNEL);
	if (!entries)
		return -ENOMEM;

#define QUEUE_ENTRY_PRIV_OFFSET(__base, __index, __limit, __esize, __psize) \
	(((char *)(__base)) + ((__limit) * (__esize)) + \
	    ((__index) * (__psize)))

	for (i = 0; i < queue->limit; i++) {
		entries[i].flags = 0;
		entries[i].queue = queue;
		entries[i].skb = NULL;
		entries[i].entry_idx = i;
		entries[i].priv_data =
		    QUEUE_ENTRY_PRIV_OFFSET(entries, i, queue->limit,
					    sizeof(*entries), queue->priv_size);
	}

#undef QUEUE_ENTRY_PRIV_OFFSET

	queue->entries = entries;

	return 0;
}