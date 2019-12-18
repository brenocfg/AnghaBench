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
struct rt2x00_dev {struct data_queue* bcn; struct rt2800_drv_data* drv_data; } ;
struct rt2800_drv_data {int /*<<< orphan*/  sta_ids; int /*<<< orphan*/ ** wcid_to_sta; } ;
struct queue_entry {int /*<<< orphan*/  flags; } ;
struct data_queue {int limit; struct queue_entry* entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENTRY_BCN_ASSIGNED ; 
 int WCID_END ; 
 int WCID_START ; 
 int /*<<< orphan*/  __clear_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void rt2800_pre_reset_hw(struct rt2x00_dev *rt2x00dev)
{
	struct rt2800_drv_data *drv_data = rt2x00dev->drv_data;
	struct data_queue *queue = rt2x00dev->bcn;
	struct queue_entry *entry;
	int i, wcid;

	for (wcid = WCID_START; wcid < WCID_END; wcid++) {
		drv_data->wcid_to_sta[wcid - WCID_START] = NULL;
		__clear_bit(wcid - WCID_START, drv_data->sta_ids);
	}

	for (i = 0; i < queue->limit; i++) {
		entry = &queue->entries[i];
		clear_bit(ENTRY_BCN_ASSIGNED, &entry->flags);
	}
}