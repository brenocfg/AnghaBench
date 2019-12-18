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
struct mlxsw_sp {TYPE_1__* sb; } ;
struct TYPE_2__ {int /*<<< orphan*/  cell_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_UP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u32 mlxsw_sp_bytes_cells(const struct mlxsw_sp *mlxsw_sp, u32 bytes)
{
	return DIV_ROUND_UP(bytes, mlxsw_sp->sb->cell_size);
}