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
struct mlxsw_afa_block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_afa_block_destroy (struct mlxsw_afa_block*) ; 

__attribute__((used)) static void
mlxsw_sp_mr_tcam_afa_block_destroy(struct mlxsw_afa_block *afa_block)
{
	mlxsw_afa_block_destroy(afa_block);
}