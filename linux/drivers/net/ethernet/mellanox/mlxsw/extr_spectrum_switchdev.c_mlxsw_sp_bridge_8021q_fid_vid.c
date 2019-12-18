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
typedef  int /*<<< orphan*/  u16 ;
struct mlxsw_sp_fid {int dummy; } ;
struct mlxsw_sp_bridge_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_sp_fid_8021q_vid (struct mlxsw_sp_fid const*) ; 

__attribute__((used)) static u16
mlxsw_sp_bridge_8021q_fid_vid(struct mlxsw_sp_bridge_device *bridge_device,
			      const struct mlxsw_sp_fid *fid)
{
	return mlxsw_sp_fid_8021q_vid(fid);
}