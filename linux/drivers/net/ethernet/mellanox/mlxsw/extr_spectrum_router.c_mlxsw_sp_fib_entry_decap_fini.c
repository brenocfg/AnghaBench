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
struct TYPE_4__ {int /*<<< orphan*/  tunnel_index; TYPE_1__* ipip_entry; } ;
struct mlxsw_sp_fib_entry {TYPE_2__ decap; } ;
struct mlxsw_sp {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/ * decap_fib_entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_SP_KVDL_ENTRY_TYPE_ADJ ; 
 int /*<<< orphan*/  mlxsw_sp_kvdl_free (struct mlxsw_sp*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlxsw_sp_fib_entry_decap_fini(struct mlxsw_sp *mlxsw_sp,
					  struct mlxsw_sp_fib_entry *fib_entry)
{
	/* Unlink this node from the IPIP entry that it's the decap entry of. */
	fib_entry->decap.ipip_entry->decap_fib_entry = NULL;
	fib_entry->decap.ipip_entry = NULL;
	mlxsw_sp_kvdl_free(mlxsw_sp, MLXSW_SP_KVDL_ENTRY_TYPE_ADJ,
			   1, fib_entry->decap.tunnel_index);
}