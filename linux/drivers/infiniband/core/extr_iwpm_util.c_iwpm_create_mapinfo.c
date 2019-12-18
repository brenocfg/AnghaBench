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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct sockaddr_storage {int dummy; } ;
struct iwpm_mapping_info {int /*<<< orphan*/  hlist_node; int /*<<< orphan*/  mapped_sockaddr; int /*<<< orphan*/  local_sockaddr; int /*<<< orphan*/  map_flags; int /*<<< orphan*/  nl_client; } ;
struct hlist_head {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct hlist_head* get_mapinfo_hash_bucket (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,struct hlist_head*) ; 
 scalar_t__ iwpm_hash_bucket ; 
 int /*<<< orphan*/  iwpm_mapinfo_lock ; 
 int /*<<< orphan*/  iwpm_valid_client (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct iwpm_mapping_info*) ; 
 struct iwpm_mapping_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct sockaddr_storage*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int iwpm_create_mapinfo(struct sockaddr_storage *local_sockaddr,
			struct sockaddr_storage *mapped_sockaddr,
			u8 nl_client, u32 map_flags)
{
	struct hlist_head *hash_bucket_head = NULL;
	struct iwpm_mapping_info *map_info;
	unsigned long flags;
	int ret = -EINVAL;

	if (!iwpm_valid_client(nl_client))
		return ret;
	map_info = kzalloc(sizeof(struct iwpm_mapping_info), GFP_KERNEL);
	if (!map_info)
		return -ENOMEM;

	memcpy(&map_info->local_sockaddr, local_sockaddr,
	       sizeof(struct sockaddr_storage));
	memcpy(&map_info->mapped_sockaddr, mapped_sockaddr,
	       sizeof(struct sockaddr_storage));
	map_info->nl_client = nl_client;
	map_info->map_flags = map_flags;

	spin_lock_irqsave(&iwpm_mapinfo_lock, flags);
	if (iwpm_hash_bucket) {
		hash_bucket_head = get_mapinfo_hash_bucket(
					&map_info->local_sockaddr,
					&map_info->mapped_sockaddr);
		if (hash_bucket_head) {
			hlist_add_head(&map_info->hlist_node, hash_bucket_head);
			ret = 0;
		}
	}
	spin_unlock_irqrestore(&iwpm_mapinfo_lock, flags);

	if (!hash_bucket_head)
		kfree(map_info);
	return ret;
}