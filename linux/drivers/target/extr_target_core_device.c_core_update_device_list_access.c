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
typedef  int /*<<< orphan*/  u64 ;
struct se_node_acl {int /*<<< orphan*/  lun_entry_mutex; } ;
struct se_dev_entry {int lun_access_ro; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct se_dev_entry* target_nacl_find_deve (struct se_node_acl*,int /*<<< orphan*/ ) ; 

void core_update_device_list_access(
	u64 mapped_lun,
	bool lun_access_ro,
	struct se_node_acl *nacl)
{
	struct se_dev_entry *deve;

	mutex_lock(&nacl->lun_entry_mutex);
	deve = target_nacl_find_deve(nacl, mapped_lun);
	if (deve)
		deve->lun_access_ro = lun_access_ro;
	mutex_unlock(&nacl->lun_entry_mutex);
}