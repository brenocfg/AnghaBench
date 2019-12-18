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
struct mlxsw_sp_fid {int /*<<< orphan*/  fid_index; TYPE_1__* fid_family; } ;
struct TYPE_2__ {int /*<<< orphan*/  mlxsw_sp; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_sp_fid_op (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mlxsw_sp_fid_dummy_deconfigure(struct mlxsw_sp_fid *fid)
{
	mlxsw_sp_fid_op(fid->fid_family->mlxsw_sp, fid->fid_index, 0, false);
}