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
typedef  scalar_t__ u16 ;
struct mlxsw_sp_fid {scalar_t__ fid_index; } ;

/* Variables and functions */
 scalar_t__ VLAN_N_VID ; 

__attribute__((used)) static u16 mlxsw_sp_fid_8021d_flood_index(const struct mlxsw_sp_fid *fid)
{
	return fid->fid_index - VLAN_N_VID;
}