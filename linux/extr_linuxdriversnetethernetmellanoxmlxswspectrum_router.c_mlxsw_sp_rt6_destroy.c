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
struct mlxsw_sp_rt6 {int /*<<< orphan*/  rt; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct mlxsw_sp_rt6*) ; 
 int /*<<< orphan*/  mlxsw_sp_rt6_release (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlxsw_sp_rt6_destroy(struct mlxsw_sp_rt6 *mlxsw_sp_rt6)
{
	mlxsw_sp_rt6_release(mlxsw_sp_rt6->rt);
	kfree(mlxsw_sp_rt6);
}