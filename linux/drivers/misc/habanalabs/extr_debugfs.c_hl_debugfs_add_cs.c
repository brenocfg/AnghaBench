#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct hl_dbg_device_entry {int /*<<< orphan*/  cs_spinlock; int /*<<< orphan*/  cs_list; } ;
struct hl_cs {int /*<<< orphan*/  debugfs_list; TYPE_2__* ctx; } ;
struct TYPE_4__ {TYPE_1__* hdev; } ;
struct TYPE_3__ {struct hl_dbg_device_entry hl_debugfs; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void hl_debugfs_add_cs(struct hl_cs *cs)
{
	struct hl_dbg_device_entry *dev_entry = &cs->ctx->hdev->hl_debugfs;

	spin_lock(&dev_entry->cs_spinlock);
	list_add(&cs->debugfs_list, &dev_entry->cs_list);
	spin_unlock(&dev_entry->cs_spinlock);
}