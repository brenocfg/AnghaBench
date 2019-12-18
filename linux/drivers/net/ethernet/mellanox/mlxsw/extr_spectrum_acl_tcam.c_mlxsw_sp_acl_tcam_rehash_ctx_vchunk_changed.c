#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * stop_ventry; int /*<<< orphan*/ * start_ventry; struct mlxsw_sp_acl_tcam_vchunk* current_vchunk; } ;
struct TYPE_4__ {TYPE_1__ ctx; } ;
struct mlxsw_sp_acl_tcam_vregion {TYPE_2__ rehash; } ;
struct mlxsw_sp_acl_tcam_vchunk {struct mlxsw_sp_acl_tcam_vregion* vregion; } ;

/* Variables and functions */

__attribute__((used)) static void
mlxsw_sp_acl_tcam_rehash_ctx_vchunk_changed(struct mlxsw_sp_acl_tcam_vchunk *vchunk)
{
	struct mlxsw_sp_acl_tcam_vregion *vregion = vchunk->vregion;

	/* If a rule was added or deleted from vchunk which is currently
	 * under rehash migration, we have to reset the ventry pointers
	 * to make sure all rules are properly migrated.
	 */
	if (vregion->rehash.ctx.current_vchunk == vchunk) {
		vregion->rehash.ctx.start_ventry = NULL;
		vregion->rehash.ctx.stop_ventry = NULL;
	}
}