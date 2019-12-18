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
struct uverbs_attr_bundle {int dummy; } ;
struct ib_dm {int dummy; } ;
struct mlx5_ib_dm {int type; struct ib_dm ibdm; } ;
struct ib_ucontext {int dummy; } ;
struct ib_dm_alloc_attr {int /*<<< orphan*/  alignment; int /*<<< orphan*/  length; } ;
struct ib_device {int dummy; } ;
typedef  enum mlx5_ib_uapi_dm_type { ____Placeholder_mlx5_ib_uapi_dm_type } mlx5_ib_uapi_dm_type ;

/* Variables and functions */
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 struct ib_dm* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MLX5_IB_ATTR_ALLOC_DM_REQ_TYPE ; 
#define  MLX5_IB_UAPI_DM_TYPE_HEADER_MODIFY_SW_ICM 130 
#define  MLX5_IB_UAPI_DM_TYPE_MEMIC 129 
#define  MLX5_IB_UAPI_DM_TYPE_STEERING_SW_ICM 128 
 int /*<<< orphan*/  MLX5_SW_ICM_TYPE_HEADER_MODIFY ; 
 int /*<<< orphan*/  MLX5_SW_ICM_TYPE_STEERING ; 
 int check_dm_type_support (int /*<<< orphan*/ ,int) ; 
 int handle_alloc_dm_memic (struct ib_ucontext*,struct mlx5_ib_dm*,struct ib_dm_alloc_attr*,struct uverbs_attr_bundle*) ; 
 int handle_alloc_dm_sw_icm (struct ib_ucontext*,struct mlx5_ib_dm*,struct ib_dm_alloc_attr*,struct uverbs_attr_bundle*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mlx5_ib_dm*) ; 
 struct mlx5_ib_dm* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_ib_dbg (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_mdev (struct ib_device*) ; 
 int uverbs_get_const_default (int*,struct uverbs_attr_bundle*,int /*<<< orphan*/ ,int) ; 

struct ib_dm *mlx5_ib_alloc_dm(struct ib_device *ibdev,
			       struct ib_ucontext *context,
			       struct ib_dm_alloc_attr *attr,
			       struct uverbs_attr_bundle *attrs)
{
	struct mlx5_ib_dm *dm;
	enum mlx5_ib_uapi_dm_type type;
	int err;

	err = uverbs_get_const_default(&type, attrs,
				       MLX5_IB_ATTR_ALLOC_DM_REQ_TYPE,
				       MLX5_IB_UAPI_DM_TYPE_MEMIC);
	if (err)
		return ERR_PTR(err);

	mlx5_ib_dbg(to_mdev(ibdev), "alloc_dm req: dm_type=%d user_length=0x%llx log_alignment=%d\n",
		    type, attr->length, attr->alignment);

	err = check_dm_type_support(to_mdev(ibdev), type);
	if (err)
		return ERR_PTR(err);

	dm = kzalloc(sizeof(*dm), GFP_KERNEL);
	if (!dm)
		return ERR_PTR(-ENOMEM);

	dm->type = type;

	switch (type) {
	case MLX5_IB_UAPI_DM_TYPE_MEMIC:
		err = handle_alloc_dm_memic(context, dm,
					    attr,
					    attrs);
		break;
	case MLX5_IB_UAPI_DM_TYPE_STEERING_SW_ICM:
		err = handle_alloc_dm_sw_icm(context, dm,
					     attr, attrs,
					     MLX5_SW_ICM_TYPE_STEERING);
		break;
	case MLX5_IB_UAPI_DM_TYPE_HEADER_MODIFY_SW_ICM:
		err = handle_alloc_dm_sw_icm(context, dm,
					     attr, attrs,
					     MLX5_SW_ICM_TYPE_HEADER_MODIFY);
		break;
	default:
		err = -EOPNOTSUPP;
	}

	if (err)
		goto err_free;

	return &dm->ibdm;

err_free:
	kfree(dm);
	return ERR_PTR(err);
}