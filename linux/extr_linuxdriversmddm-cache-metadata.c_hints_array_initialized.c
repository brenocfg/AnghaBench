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
struct dm_cache_metadata {scalar_t__ policy_hint_size; scalar_t__ hint_root; } ;

/* Variables and functions */

__attribute__((used)) static bool hints_array_initialized(struct dm_cache_metadata *cmd)
{
	return cmd->hint_root && cmd->policy_hint_size;
}