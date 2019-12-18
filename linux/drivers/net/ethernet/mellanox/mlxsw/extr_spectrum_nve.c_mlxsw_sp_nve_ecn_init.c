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
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int mlxsw_sp_nve_ecn_decap_init (struct mlxsw_sp*) ; 
 int mlxsw_sp_nve_ecn_encap_init (struct mlxsw_sp*) ; 

__attribute__((used)) static int mlxsw_sp_nve_ecn_init(struct mlxsw_sp *mlxsw_sp)
{
	int err;

	err = mlxsw_sp_nve_ecn_encap_init(mlxsw_sp);
	if (err)
		return err;

	return mlxsw_sp_nve_ecn_decap_init(mlxsw_sp);
}