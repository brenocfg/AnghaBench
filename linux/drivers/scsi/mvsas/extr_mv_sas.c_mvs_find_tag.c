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
typedef  int /*<<< orphan*/  u32 ;
struct sas_task {struct mvs_slot_info* lldd_task; } ;
struct mvs_slot_info {int /*<<< orphan*/  slot_tag; } ;
struct mvs_info {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int mvs_find_tag(struct mvs_info *mvi, struct sas_task *task, u32 *tag)
{
	if (task->lldd_task) {
		struct mvs_slot_info *slot;
		slot = task->lldd_task;
		*tag = slot->slot_tag;
		return 1;
	}
	return 0;
}