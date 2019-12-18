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
struct mlxsw_sp_ipip_entry {TYPE_1__* ol_lb; } ;
struct TYPE_2__ {int /*<<< orphan*/  common; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct mlxsw_sp_ipip_entry*) ; 
 int /*<<< orphan*/  mlxsw_sp_rif_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mlxsw_sp_ipip_entry_dealloc(struct mlxsw_sp_ipip_entry *ipip_entry)
{
	mlxsw_sp_rif_destroy(&ipip_entry->ol_lb->common);
	kfree(ipip_entry);
}