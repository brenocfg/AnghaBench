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
typedef  void* u8 ;
typedef  struct applesmc_entry {int valid; void* flags; int /*<<< orphan*/  type; void* len; int /*<<< orphan*/  key; } const applesmc_entry ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {int /*<<< orphan*/  mutex; struct applesmc_entry const* cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  APPLESMC_GET_KEY_BY_INDEX_CMD ; 
 int /*<<< orphan*/  APPLESMC_GET_KEY_TYPE_CMD ; 
 struct applesmc_entry const* ERR_PTR (int) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void**,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int read_smc (int /*<<< orphan*/ ,void**,void**,int) ; 
 TYPE_1__ smcreg ; 

__attribute__((used)) static const struct applesmc_entry *applesmc_get_entry_by_index(int index)
{
	struct applesmc_entry *cache = &smcreg.cache[index];
	u8 key[4], info[6];
	__be32 be;
	int ret = 0;

	if (cache->valid)
		return cache;

	mutex_lock(&smcreg.mutex);

	if (cache->valid)
		goto out;
	be = cpu_to_be32(index);
	ret = read_smc(APPLESMC_GET_KEY_BY_INDEX_CMD, (u8 *)&be, key, 4);
	if (ret)
		goto out;
	ret = read_smc(APPLESMC_GET_KEY_TYPE_CMD, key, info, 6);
	if (ret)
		goto out;

	memcpy(cache->key, key, 4);
	cache->len = info[0];
	memcpy(cache->type, &info[1], 4);
	cache->flags = info[5];
	cache->valid = 1;

out:
	mutex_unlock(&smcreg.mutex);
	if (ret)
		return ERR_PTR(ret);
	return cache;
}