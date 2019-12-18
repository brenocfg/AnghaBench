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
struct TYPE_3__ {int /*<<< orphan*/ * current_vchunk; } ;
struct TYPE_4__ {TYPE_1__ ctx; } ;
struct mlxsw_sp_acl_tcam_vregion {TYPE_2__ rehash; } ;

/* Variables and functions */

__attribute__((used)) static void
mlxsw_sp_acl_tcam_rehash_ctx_vregion_changed(struct mlxsw_sp_acl_tcam_vregion *vregion)
{
	/* If a chunk was added or deleted from vregion we have to reset
	 * the current chunk pointer to make sure all chunks
	 * are properly migrated.
	 */
	vregion->rehash.ctx.current_vchunk = NULL;
}