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
struct queue_entry {scalar_t__ last_action; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENTRY_OWNER_DEVICE_DATA ; 
 int /*<<< orphan*/  jiffies ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int time_after (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline int rt2x00queue_dma_timeout(struct queue_entry *entry)
{
	if (!test_bit(ENTRY_OWNER_DEVICE_DATA, &entry->flags))
		return false;
	return time_after(jiffies, entry->last_action + msecs_to_jiffies(100));
}