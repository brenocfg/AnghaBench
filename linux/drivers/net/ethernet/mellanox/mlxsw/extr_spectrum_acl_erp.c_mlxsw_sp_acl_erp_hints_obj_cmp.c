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
struct mlxsw_sp_acl_erp_key {int /*<<< orphan*/  mask; } ;

/* Variables and functions */
 int memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mlxsw_sp_acl_erp_hints_obj_cmp(const void *obj1, const void *obj2)
{
	const struct mlxsw_sp_acl_erp_key *key1 = obj1;
	const struct mlxsw_sp_acl_erp_key *key2 = obj2;

	/* For hints purposes, two objects are considered equal
	 * in case the masks are the same. Does not matter what
	 * the "ctcam" value is.
	 */
	return memcmp(key1->mask, key2->mask, sizeof(key1->mask));
}