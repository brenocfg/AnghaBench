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
struct rt2x00_dev {int /*<<< orphan*/  flags; } ;
struct queue_entry {TYPE_1__* queue; int /*<<< orphan*/  entry_idx; scalar_t__ last_action; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  qid; int /*<<< orphan*/  rt2x00dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_STATE_FLUSHING ; 
 int /*<<< orphan*/  ENTRY_DATA_STATUS_PENDING ; 
 int /*<<< orphan*/  jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  rt2x00_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int time_after (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline bool rt2800_entry_txstatus_timeout(struct rt2x00_dev *rt2x00dev,
						 struct queue_entry *entry)
{
	bool ret;
	unsigned long tout;

	if (!test_bit(ENTRY_DATA_STATUS_PENDING, &entry->flags))
		return false;

	if (test_bit(DEVICE_STATE_FLUSHING, &rt2x00dev->flags))
		tout = msecs_to_jiffies(50);
	else
		tout = msecs_to_jiffies(2000);

	ret = time_after(jiffies, entry->last_action + tout);
	if (unlikely(ret))
		rt2x00_dbg(entry->queue->rt2x00dev,
			   "TX status timeout for entry %d in queue %d\n",
			   entry->entry_idx, entry->queue->qid);
	return ret;
}