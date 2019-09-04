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
struct mlxsw_sp_fid {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  vid; } ;

/* Variables and functions */
 TYPE_1__* mlxsw_sp_fid_8021q_fid (struct mlxsw_sp_fid const*) ; 

u16 mlxsw_sp_fid_8021q_vid(const struct mlxsw_sp_fid *fid)
{
	return mlxsw_sp_fid_8021q_fid(fid)->vid;
}