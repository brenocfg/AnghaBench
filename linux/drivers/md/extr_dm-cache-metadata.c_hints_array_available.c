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
struct dm_cache_metadata {scalar_t__ clean_when_opened; } ;

/* Variables and functions */
 scalar_t__ hints_array_initialized (struct dm_cache_metadata*) ; 
 scalar_t__ policy_unchanged (struct dm_cache_metadata*,struct dm_cache_policy*) ; 

__attribute__((used)) static bool hints_array_available(struct dm_cache_metadata *cmd,
				  struct dm_cache_policy *policy)
{
	return cmd->clean_when_opened && policy_unchanged(cmd, policy) &&
		hints_array_initialized(cmd);
}