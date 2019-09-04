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
struct fw_cfg_sysfs_entry {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  fw_cfg_cache_lock ; 
 int /*<<< orphan*/  fw_cfg_entry_cache ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void fw_cfg_sysfs_cache_enlist(struct fw_cfg_sysfs_entry *entry)
{
	spin_lock(&fw_cfg_cache_lock);
	list_add_tail(&entry->list, &fw_cfg_entry_cache);
	spin_unlock(&fw_cfg_cache_lock);
}