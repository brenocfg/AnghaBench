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
struct iwpm_remote_info {int /*<<< orphan*/  hlist_node; int /*<<< orphan*/  mapped_rem_sockaddr; int /*<<< orphan*/  mapped_loc_sockaddr; } ;
struct hlist_head {int dummy; } ;

/* Variables and functions */
 struct hlist_head* get_reminfo_hash_bucket (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,struct hlist_head*) ; 
 scalar_t__ iwpm_reminfo_bucket ; 
 int /*<<< orphan*/  iwpm_reminfo_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void iwpm_add_remote_info(struct iwpm_remote_info *rem_info)
{
	struct hlist_head *hash_bucket_head;
	unsigned long flags;

	spin_lock_irqsave(&iwpm_reminfo_lock, flags);
	if (iwpm_reminfo_bucket) {
		hash_bucket_head = get_reminfo_hash_bucket(
					&rem_info->mapped_loc_sockaddr,
					&rem_info->mapped_rem_sockaddr);
		if (hash_bucket_head)
			hlist_add_head(&rem_info->hlist_node, hash_bucket_head);
	}
	spin_unlock_irqrestore(&iwpm_reminfo_lock, flags);
}