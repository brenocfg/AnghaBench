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
struct mlxsw_sp2_acl_tcam_region {int /*<<< orphan*/  aregion; } ;
struct mlxsw_sp2_acl_tcam_chunk {int /*<<< orphan*/  achunk; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_sp_acl_atcam_chunk_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static void mlxsw_sp2_acl_tcam_chunk_init(void *region_priv, void *chunk_priv,
					  unsigned int priority)
{
	struct mlxsw_sp2_acl_tcam_region *region = region_priv;
	struct mlxsw_sp2_acl_tcam_chunk *chunk = chunk_priv;

	mlxsw_sp_acl_atcam_chunk_init(&region->aregion, &chunk->achunk,
				      priority);
}