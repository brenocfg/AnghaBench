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
struct mlxsw_sp_ipip_entry {int /*<<< orphan*/  ipip_list_node; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_sp_ipip_entry_dealloc (struct mlxsw_sp_ipip_entry*) ; 

__attribute__((used)) static void
mlxsw_sp_ipip_entry_destroy(struct mlxsw_sp *mlxsw_sp,
			    struct mlxsw_sp_ipip_entry *ipip_entry)
{
	list_del(&ipip_entry->ipip_list_node);
	mlxsw_sp_ipip_entry_dealloc(ipip_entry);
}