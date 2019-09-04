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
struct TYPE_3__ {scalar_t__ dest_port; } ;
struct mlxsw_sp_span_entry {TYPE_2__* ops; TYPE_1__ parms; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* deconfigure ) (struct mlxsw_sp_span_entry*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct mlxsw_sp_span_entry*) ; 

__attribute__((used)) static void
mlxsw_sp_span_entry_deconfigure(struct mlxsw_sp_span_entry *span_entry)
{
	if (span_entry->parms.dest_port)
		span_entry->ops->deconfigure(span_entry);
}