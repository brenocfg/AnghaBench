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
typedef  int /*<<< orphan*/  u32 ;
struct ib_uobject {struct devx_obj* object; } ;
struct devx_obj {int /*<<< orphan*/  dinlen; int /*<<< orphan*/  dinbox; int /*<<< orphan*/  mdev; } ;
typedef  int /*<<< orphan*/  out ;
typedef  enum rdma_remove_reason { ____Placeholder_rdma_remove_reason } rdma_remove_reason ;

/* Variables and functions */
 int MLX5_ST_SZ_DW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  general_obj_out_cmd_hdr ; 
 scalar_t__ ib_is_destroy_retryable (int,int,struct ib_uobject*) ; 
 int /*<<< orphan*/  kfree (struct devx_obj*) ; 
 int mlx5_cmd_exec (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int devx_obj_cleanup(struct ib_uobject *uobject,
			    enum rdma_remove_reason why)
{
	u32 out[MLX5_ST_SZ_DW(general_obj_out_cmd_hdr)];
	struct devx_obj *obj = uobject->object;
	int ret;

	ret = mlx5_cmd_exec(obj->mdev, obj->dinbox, obj->dinlen, out, sizeof(out));
	if (ib_is_destroy_retryable(ret, why, uobject))
		return ret;

	kfree(obj);
	return ret;
}