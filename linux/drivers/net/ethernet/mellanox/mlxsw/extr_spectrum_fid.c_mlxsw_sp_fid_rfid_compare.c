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
typedef  scalar_t__ u16 ;
struct mlxsw_sp_fid {scalar_t__ fid_index; TYPE_1__* fid_family; } ;
struct TYPE_2__ {scalar_t__ start_index; } ;

/* Variables and functions */

__attribute__((used)) static bool mlxsw_sp_fid_rfid_compare(const struct mlxsw_sp_fid *fid,
				      const void *arg)
{
	u16 rif_index = *(u16 *) arg;

	return fid->fid_index == rif_index + fid->fid_family->start_index;
}