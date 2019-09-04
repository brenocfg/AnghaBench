#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int nr_areas; int pages_per_area; int /*<<< orphan*/  lock; scalar_t__*** areas; scalar_t__* active_pages; scalar_t__* active_entries; scalar_t__ active_area; } ;
typedef  TYPE_1__ debug_info_t ;

/* Variables and functions */
 int DEBUG_FLUSH_ALL ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void debug_flush(debug_info_t *id, int area)
{
	unsigned long flags;
	int i, j;

	if (!id || !id->areas)
		return;
	spin_lock_irqsave(&id->lock, flags);
	if (area == DEBUG_FLUSH_ALL) {
		id->active_area = 0;
		memset(id->active_entries, 0, id->nr_areas * sizeof(int));
		for (i = 0; i < id->nr_areas; i++) {
			id->active_pages[i] = 0;
			for (j = 0; j < id->pages_per_area; j++)
				memset(id->areas[i][j], 0, PAGE_SIZE);
		}
	} else if (area >= 0 && area < id->nr_areas) {
		id->active_entries[area] = 0;
		id->active_pages[area] = 0;
		for (i = 0; i < id->pages_per_area; i++)
			memset(id->areas[area][i], 0, PAGE_SIZE);
	}
	spin_unlock_irqrestore(&id->lock, flags);
}