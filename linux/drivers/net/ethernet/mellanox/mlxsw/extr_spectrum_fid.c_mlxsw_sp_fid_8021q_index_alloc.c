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
struct mlxsw_sp_fid_family {scalar_t__ start_index; scalar_t__ end_index; } ;
struct mlxsw_sp_fid {struct mlxsw_sp_fid_family* fid_family; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int mlxsw_sp_fid_8021q_index_alloc(struct mlxsw_sp_fid *fid,
					  const void *arg, u16 *p_fid_index)
{
	struct mlxsw_sp_fid_family *fid_family = fid->fid_family;
	u16 vid = *(u16 *) arg;

	/* Use 1:1 mapping for simplicity although not a must */
	if (vid < fid_family->start_index || vid > fid_family->end_index)
		return -EINVAL;
	*p_fid_index = vid;

	return 0;
}