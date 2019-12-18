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
struct dm_cache_metadata {unsigned int const* policy_version; size_t policy_hint_size; int /*<<< orphan*/  policy_name; } ;

/* Variables and functions */
 size_t dm_cache_policy_get_hint_size (struct dm_cache_policy*) ; 
 char* dm_cache_policy_get_name (struct dm_cache_policy*) ; 
 unsigned int* dm_cache_policy_get_version (struct dm_cache_policy*) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static bool policy_unchanged(struct dm_cache_metadata *cmd,
			     struct dm_cache_policy *policy)
{
	const char *policy_name = dm_cache_policy_get_name(policy);
	const unsigned *policy_version = dm_cache_policy_get_version(policy);
	size_t policy_hint_size = dm_cache_policy_get_hint_size(policy);

	/*
	 * Ensure policy names match.
	 */
	if (strncmp(cmd->policy_name, policy_name, sizeof(cmd->policy_name)))
		return false;

	/*
	 * Ensure policy major versions match.
	 */
	if (cmd->policy_version[0] != policy_version[0])
		return false;

	/*
	 * Ensure policy hint sizes match.
	 */
	if (cmd->policy_hint_size != policy_hint_size)
		return false;

	return true;
}