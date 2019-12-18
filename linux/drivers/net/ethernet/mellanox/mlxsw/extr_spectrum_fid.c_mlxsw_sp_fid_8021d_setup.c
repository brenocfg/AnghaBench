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
struct mlxsw_sp_fid {int dummy; } ;
struct TYPE_2__ {int br_ifindex; } ;

/* Variables and functions */
 TYPE_1__* mlxsw_sp_fid_8021d_fid (struct mlxsw_sp_fid*) ; 

__attribute__((used)) static void mlxsw_sp_fid_8021d_setup(struct mlxsw_sp_fid *fid, const void *arg)
{
	int br_ifindex = *(int *) arg;

	mlxsw_sp_fid_8021d_fid(fid)->br_ifindex = br_ifindex;
}