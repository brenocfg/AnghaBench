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
typedef  int /*<<< orphan*/  u16 ;
struct mlxsw_sp_fid {TYPE_1__* fid_family; } ;
struct TYPE_2__ {int /*<<< orphan*/  start_index; } ;

/* Variables and functions */

__attribute__((used)) static int mlxsw_sp_fid_dummy_index_alloc(struct mlxsw_sp_fid *fid,
					  const void *arg, u16 *p_fid_index)
{
	*p_fid_index = fid->fid_family->start_index;

	return 0;
}