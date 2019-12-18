#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  void* u32 ;
struct mlx5_mtt {int dummy; } ;
struct mlx5_klm {int dummy; } ;
struct mlx5_ib_mr {TYPE_5__* sig; TYPE_7__* klm_mr; TYPE_7__* mtt_mr; } ;
struct mlx5_ib_dev {int /*<<< orphan*/  mdev; } ;
struct ib_pd {int /*<<< orphan*/  device; } ;
struct TYPE_10__ {int /*<<< orphan*/  device; } ;
struct TYPE_15__ {TYPE_1__ ibmr; } ;
struct TYPE_12__ {void* psv_idx; } ;
struct TYPE_11__ {void* psv_idx; } ;
struct TYPE_14__ {int sig_status_checked; int sig_err_exists; TYPE_3__ psv_wire; TYPE_2__ psv_memory; int /*<<< orphan*/  sigerr_count; } ;
struct TYPE_13__ {int /*<<< orphan*/  pdn; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (TYPE_7__*) ; 
 void* MLX5_ADDR_OF (int /*<<< orphan*/ ,void**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_MKC_ACCESS_MODE_KLMS ; 
 int /*<<< orphan*/  MLX5_MKC_ACCESS_MODE_MTT ; 
 int MLX5_MKEY_BSF_OCTO_SIZE ; 
 int /*<<< orphan*/  MLX5_SET (void*,void*,int /*<<< orphan*/ ,int) ; 
 int PTR_ERR (TYPE_7__*) ; 
 int _mlx5_alloc_mkey_descs (struct ib_pd*,struct mlx5_ib_mr*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**,int) ; 
 int /*<<< orphan*/  bsf_en ; 
 int /*<<< orphan*/  bsf_octword_size ; 
 int /*<<< orphan*/  create_mkey_in ; 
 int /*<<< orphan*/  dereg_mr (struct mlx5_ib_dev*,TYPE_7__*) ; 
 int /*<<< orphan*/  kfree (TYPE_5__*) ; 
 TYPE_5__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memory_key_mkey_entry ; 
 int mlx5_core_create_psv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,void**) ; 
 scalar_t__ mlx5_core_destroy_psv (int /*<<< orphan*/ ,void*) ; 
 void* mlx5_ib_alloc_pi_mr (struct ib_pd*,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_ib_warn (struct mlx5_ib_dev*,char*,void*) ; 
 struct mlx5_ib_dev* to_mdev (int /*<<< orphan*/ ) ; 
 TYPE_4__* to_mpd (struct ib_pd*) ; 

__attribute__((used)) static int mlx5_alloc_integrity_descs(struct ib_pd *pd, struct mlx5_ib_mr *mr,
				      int max_num_sg, int max_num_meta_sg,
				      u32 *in, int inlen)
{
	struct mlx5_ib_dev *dev = to_mdev(pd->device);
	u32 psv_index[2];
	void *mkc;
	int err;

	mr->sig = kzalloc(sizeof(*mr->sig), GFP_KERNEL);
	if (!mr->sig)
		return -ENOMEM;

	/* create mem & wire PSVs */
	err = mlx5_core_create_psv(dev->mdev, to_mpd(pd)->pdn, 2, psv_index);
	if (err)
		goto err_free_sig;

	mr->sig->psv_memory.psv_idx = psv_index[0];
	mr->sig->psv_wire.psv_idx = psv_index[1];

	mr->sig->sig_status_checked = true;
	mr->sig->sig_err_exists = false;
	/* Next UMR, Arm SIGERR */
	++mr->sig->sigerr_count;
	mr->klm_mr = mlx5_ib_alloc_pi_mr(pd, max_num_sg, max_num_meta_sg,
					 sizeof(struct mlx5_klm),
					 MLX5_MKC_ACCESS_MODE_KLMS);
	if (IS_ERR(mr->klm_mr)) {
		err = PTR_ERR(mr->klm_mr);
		goto err_destroy_psv;
	}
	mr->mtt_mr = mlx5_ib_alloc_pi_mr(pd, max_num_sg, max_num_meta_sg,
					 sizeof(struct mlx5_mtt),
					 MLX5_MKC_ACCESS_MODE_MTT);
	if (IS_ERR(mr->mtt_mr)) {
		err = PTR_ERR(mr->mtt_mr);
		goto err_free_klm_mr;
	}

	/* Set bsf descriptors for mkey */
	mkc = MLX5_ADDR_OF(create_mkey_in, in, memory_key_mkey_entry);
	MLX5_SET(mkc, mkc, bsf_en, 1);
	MLX5_SET(mkc, mkc, bsf_octword_size, MLX5_MKEY_BSF_OCTO_SIZE);

	err = _mlx5_alloc_mkey_descs(pd, mr, 4, sizeof(struct mlx5_klm), 0,
				     MLX5_MKC_ACCESS_MODE_KLMS, in, inlen);
	if (err)
		goto err_free_mtt_mr;

	return 0;

err_free_mtt_mr:
	dereg_mr(to_mdev(mr->mtt_mr->ibmr.device), mr->mtt_mr);
	mr->mtt_mr = NULL;
err_free_klm_mr:
	dereg_mr(to_mdev(mr->klm_mr->ibmr.device), mr->klm_mr);
	mr->klm_mr = NULL;
err_destroy_psv:
	if (mlx5_core_destroy_psv(dev->mdev, mr->sig->psv_memory.psv_idx))
		mlx5_ib_warn(dev, "failed to destroy mem psv %d\n",
			     mr->sig->psv_memory.psv_idx);
	if (mlx5_core_destroy_psv(dev->mdev, mr->sig->psv_wire.psv_idx))
		mlx5_ib_warn(dev, "failed to destroy wire psv %d\n",
			     mr->sig->psv_wire.psv_idx);
err_free_sig:
	kfree(mr->sig);

	return err;
}