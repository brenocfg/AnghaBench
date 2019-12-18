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
struct mlxsw_sp_mr_tcam_erif_list {int /*<<< orphan*/  kvdl_index; int /*<<< orphan*/  erif_sublists; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_splice (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mlxsw_sp_mr_erif_list_move(struct mlxsw_sp_mr_tcam_erif_list *to,
				       struct mlxsw_sp_mr_tcam_erif_list *from)
{
	list_splice(&from->erif_sublists, &to->erif_sublists);
	to->kvdl_index = from->kvdl_index;
}