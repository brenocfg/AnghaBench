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
struct mlxsw_sp_rt6 {struct fib6_info* rt; } ;
struct fib6_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct mlxsw_sp_rt6* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  fib6_info_hold (struct fib6_info*) ; 
 struct mlxsw_sp_rt6* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mlxsw_sp_rt6 *mlxsw_sp_rt6_create(struct fib6_info *rt)
{
	struct mlxsw_sp_rt6 *mlxsw_sp_rt6;

	mlxsw_sp_rt6 = kzalloc(sizeof(*mlxsw_sp_rt6), GFP_KERNEL);
	if (!mlxsw_sp_rt6)
		return ERR_PTR(-ENOMEM);

	/* In case of route replace, replaced route is deleted with
	 * no notification. Take reference to prevent accessing freed
	 * memory.
	 */
	mlxsw_sp_rt6->rt = rt;
	fib6_info_hold(rt);

	return mlxsw_sp_rt6;
}