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
struct dm_cache_metadata {int /*<<< orphan*/  tm; int /*<<< orphan*/  hint_info; scalar_t__ policy_hint_size; int /*<<< orphan*/  info; } ;
struct dm_btree_value_type {int size; int /*<<< orphan*/ * equal; int /*<<< orphan*/ * dec; int /*<<< orphan*/ * inc; int /*<<< orphan*/ * context; } ;
typedef  int /*<<< orphan*/  __le64 ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  dm_array_info_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct dm_btree_value_type*) ; 

__attribute__((used)) static void __setup_mapping_info(struct dm_cache_metadata *cmd)
{
	struct dm_btree_value_type vt;

	vt.context = NULL;
	vt.size = sizeof(__le64);
	vt.inc = NULL;
	vt.dec = NULL;
	vt.equal = NULL;
	dm_array_info_init(&cmd->info, cmd->tm, &vt);

	if (cmd->policy_hint_size) {
		vt.size = sizeof(__le32);
		dm_array_info_init(&cmd->hint_info, cmd->tm, &vt);
	}
}