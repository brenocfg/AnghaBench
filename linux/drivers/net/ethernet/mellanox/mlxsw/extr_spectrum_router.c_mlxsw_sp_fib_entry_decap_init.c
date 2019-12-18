#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct mlxsw_sp_ipip_entry {struct mlxsw_sp_fib_entry* decap_fib_entry; } ;
struct TYPE_2__ {int /*<<< orphan*/  tunnel_index; struct mlxsw_sp_ipip_entry* ipip_entry; } ;
struct mlxsw_sp_fib_entry {TYPE_1__ decap; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_SP_KVDL_ENTRY_TYPE_ADJ ; 
 int mlxsw_sp_kvdl_alloc (struct mlxsw_sp*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mlxsw_sp_fib_entry_decap_init(struct mlxsw_sp *mlxsw_sp,
			      struct mlxsw_sp_fib_entry *fib_entry,
			      struct mlxsw_sp_ipip_entry *ipip_entry)
{
	u32 tunnel_index;
	int err;

	err = mlxsw_sp_kvdl_alloc(mlxsw_sp, MLXSW_SP_KVDL_ENTRY_TYPE_ADJ,
				  1, &tunnel_index);
	if (err)
		return err;

	ipip_entry->decap_fib_entry = fib_entry;
	fib_entry->decap.ipip_entry = ipip_entry;
	fib_entry->decap.tunnel_index = tunnel_index;
	return 0;
}