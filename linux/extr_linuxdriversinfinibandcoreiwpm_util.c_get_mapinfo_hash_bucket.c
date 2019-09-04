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
typedef  size_t u32 ;
struct sockaddr_storage {int dummy; } ;
struct hlist_head {int dummy; } ;

/* Variables and functions */
 size_t IWPM_MAPINFO_HASH_MASK ; 
 int get_hash_bucket (struct sockaddr_storage*,struct sockaddr_storage*,size_t*) ; 
 struct hlist_head* iwpm_hash_bucket ; 

__attribute__((used)) static struct hlist_head *get_mapinfo_hash_bucket(struct sockaddr_storage
				*local_sockaddr, struct sockaddr_storage
				*mapped_sockaddr)
{
	u32 hash;
	int ret;

	ret = get_hash_bucket(local_sockaddr, mapped_sockaddr, &hash);
	if (ret)
		return NULL;
	return &iwpm_hash_bucket[hash & IWPM_MAPINFO_HASH_MASK];
}