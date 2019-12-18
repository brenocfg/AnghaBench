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
struct dm_cache_policy {int dummy; } ;
struct dm_cache_metadata {size_t policy_hint_size; int /*<<< orphan*/  cache_blocks; scalar_t__ hint_root; int /*<<< orphan*/  hint_info; int /*<<< orphan*/  policy_version; int /*<<< orphan*/  policy_name; } ;

/* Variables and functions */
 int EINVAL ; 
 int dm_array_del (int /*<<< orphan*/ *,scalar_t__) ; 
 int dm_array_new (int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dm_cache_policy*) ; 
 size_t dm_cache_policy_get_hint_size (struct dm_cache_policy*) ; 
 char* dm_cache_policy_get_name (struct dm_cache_policy*) ; 
 unsigned int* dm_cache_policy_get_version (struct dm_cache_policy*) ; 
 int /*<<< orphan*/  from_cblock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_hint ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned int const*,int) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static int write_hints(struct dm_cache_metadata *cmd, struct dm_cache_policy *policy)
{
	int r;
	size_t hint_size;
	const char *policy_name = dm_cache_policy_get_name(policy);
	const unsigned *policy_version = dm_cache_policy_get_version(policy);

	if (!policy_name[0] ||
	    (strlen(policy_name) > sizeof(cmd->policy_name) - 1))
		return -EINVAL;

	strncpy(cmd->policy_name, policy_name, sizeof(cmd->policy_name));
	memcpy(cmd->policy_version, policy_version, sizeof(cmd->policy_version));

	hint_size = dm_cache_policy_get_hint_size(policy);
	if (!hint_size)
		return 0; /* short-circuit hints initialization */
	cmd->policy_hint_size = hint_size;

	if (cmd->hint_root) {
		r = dm_array_del(&cmd->hint_info, cmd->hint_root);
		if (r)
			return r;
	}

	return dm_array_new(&cmd->hint_info, &cmd->hint_root,
			    from_cblock(cmd->cache_blocks),
			    get_hint, policy);
}