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
struct net_device {int dummy; } ;
struct mlxsw_sp_fid {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  br_fdb_clear_offload (struct net_device const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_fid_8021q_vid (struct mlxsw_sp_fid const*) ; 

__attribute__((used)) static void
mlxsw_sp_fid_8021q_fdb_clear_offload(const struct mlxsw_sp_fid *fid,
				     const struct net_device *nve_dev)
{
	br_fdb_clear_offload(nve_dev, mlxsw_sp_fid_8021q_vid(fid));
}