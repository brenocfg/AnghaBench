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
typedef  int /*<<< orphan*/  uint32_t ;
struct dm_cache_policy {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  policy_get_hint (struct dm_cache_policy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_cblock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_hint(uint32_t index, void *value_le, void *context)
{
	uint32_t value;
	struct dm_cache_policy *policy = context;

	value = policy_get_hint(policy, to_cblock(index));
	*((__le32 *) value_le) = cpu_to_le32(value);

	return 0;
}