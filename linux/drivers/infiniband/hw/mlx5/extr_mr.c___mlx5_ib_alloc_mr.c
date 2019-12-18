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
struct ib_mr {int /*<<< orphan*/  device; } ;
struct mlx5_ib_mr {struct ib_mr ibmr; int /*<<< orphan*/ * umem; } ;
typedef  struct mlx5_ib_mr u32 ;
struct mlx5_ib_dev {int dummy; } ;
struct ib_pd {int /*<<< orphan*/  device; } ;
typedef  enum ib_mr_type { ____Placeholder_ib_mr_type } ib_mr_type ;

/* Variables and functions */
 int ALIGN (struct mlx5_ib_mr,int) ; 
 int EINVAL ; 
 int ENOMEM ; 
 struct ib_mr* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  IB_MR_TYPE_INTEGRITY 130 
#define  IB_MR_TYPE_MEM_REG 129 
#define  IB_MR_TYPE_SG_GAPS 128 
 int MLX5_ST_SZ_BYTES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_mkey_in ; 
 int /*<<< orphan*/  kfree (struct mlx5_ib_mr*) ; 
 struct mlx5_ib_mr* kzalloc (int,int /*<<< orphan*/ ) ; 
 int mlx5_alloc_integrity_descs (struct ib_pd*,struct mlx5_ib_mr*,struct mlx5_ib_mr,struct mlx5_ib_mr,struct mlx5_ib_mr*,int) ; 
 int mlx5_alloc_mem_reg_descs (struct ib_pd*,struct mlx5_ib_mr*,int,struct mlx5_ib_mr*,int) ; 
 int mlx5_alloc_sg_gaps_descs (struct ib_pd*,struct mlx5_ib_mr*,int,struct mlx5_ib_mr*,int) ; 
 int /*<<< orphan*/  mlx5_ib_warn (struct mlx5_ib_dev*,char*,int) ; 
 struct mlx5_ib_dev* to_mdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ib_mr *__mlx5_ib_alloc_mr(struct ib_pd *pd,
					enum ib_mr_type mr_type, u32 max_num_sg,
					u32 max_num_meta_sg)
{
	struct mlx5_ib_dev *dev = to_mdev(pd->device);
	int inlen = MLX5_ST_SZ_BYTES(create_mkey_in);
	int ndescs = ALIGN(max_num_sg, 4);
	struct mlx5_ib_mr *mr;
	u32 *in;
	int err;

	mr = kzalloc(sizeof(*mr), GFP_KERNEL);
	if (!mr)
		return ERR_PTR(-ENOMEM);

	in = kzalloc(inlen, GFP_KERNEL);
	if (!in) {
		err = -ENOMEM;
		goto err_free;
	}

	mr->ibmr.device = pd->device;
	mr->umem = NULL;

	switch (mr_type) {
	case IB_MR_TYPE_MEM_REG:
		err = mlx5_alloc_mem_reg_descs(pd, mr, ndescs, in, inlen);
		break;
	case IB_MR_TYPE_SG_GAPS:
		err = mlx5_alloc_sg_gaps_descs(pd, mr, ndescs, in, inlen);
		break;
	case IB_MR_TYPE_INTEGRITY:
		err = mlx5_alloc_integrity_descs(pd, mr, max_num_sg,
						 max_num_meta_sg, in, inlen);
		break;
	default:
		mlx5_ib_warn(dev, "Invalid mr type %d\n", mr_type);
		err = -EINVAL;
	}

	if (err)
		goto err_free_in;

	kfree(in);

	return &mr->ibmr;

err_free_in:
	kfree(in);
err_free:
	kfree(mr);
	return ERR_PTR(err);
}