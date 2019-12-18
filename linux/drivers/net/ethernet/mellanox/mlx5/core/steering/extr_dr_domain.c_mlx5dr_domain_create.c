#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  log_icm_size; } ;
struct TYPE_4__ {int /*<<< orphan*/  supp_sw_steering; TYPE_1__ caps; int /*<<< orphan*/  max_log_sw_icm_sz; int /*<<< orphan*/  max_log_action_icm_sz; } ;
struct mlx5dr_domain {int type; TYPE_2__ info; int /*<<< orphan*/  mutex; int /*<<< orphan*/  refcount; struct mlx5_core_dev* mdev; } ;
struct mlx5_core_dev {int dummy; } ;
typedef  enum mlx5dr_domain_type { ____Placeholder_mlx5dr_domain_type } mlx5dr_domain_type ;

/* Variables and functions */
 int /*<<< orphan*/  DR_CHUNK_SIZE_1024K ; 
 int /*<<< orphan*/  DR_CHUNK_SIZE_4K ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MLX5DR_DOMAIN_TYPE_FDB ; 
 scalar_t__ dr_domain_caps_init (struct mlx5_core_dev*,struct mlx5dr_domain*) ; 
 int /*<<< orphan*/  dr_domain_caps_uninit (struct mlx5dr_domain*) ; 
 int dr_domain_init_cache (struct mlx5dr_domain*) ; 
 int dr_domain_init_resources (struct mlx5dr_domain*) ; 
 int /*<<< orphan*/  dr_domain_uninit_resources (struct mlx5dr_domain*) ; 
 int /*<<< orphan*/  kfree (struct mlx5dr_domain*) ; 
 struct mlx5dr_domain* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min_t (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5dr_crc32_init_table () ; 
 int /*<<< orphan*/  mlx5dr_dbg (struct mlx5dr_domain*,char*) ; 
 int /*<<< orphan*/  mlx5dr_err (struct mlx5dr_domain*,char*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  u32 ; 

struct mlx5dr_domain *
mlx5dr_domain_create(struct mlx5_core_dev *mdev, enum mlx5dr_domain_type type)
{
	struct mlx5dr_domain *dmn;
	int ret;

	if (type > MLX5DR_DOMAIN_TYPE_FDB)
		return NULL;

	dmn = kzalloc(sizeof(*dmn), GFP_KERNEL);
	if (!dmn)
		return NULL;

	dmn->mdev = mdev;
	dmn->type = type;
	refcount_set(&dmn->refcount, 1);
	mutex_init(&dmn->mutex);

	if (dr_domain_caps_init(mdev, dmn)) {
		mlx5dr_dbg(dmn, "Failed init domain, no caps\n");
		goto free_domain;
	}

	dmn->info.max_log_action_icm_sz = DR_CHUNK_SIZE_4K;
	dmn->info.max_log_sw_icm_sz = min_t(u32, DR_CHUNK_SIZE_1024K,
					    dmn->info.caps.log_icm_size);

	if (!dmn->info.supp_sw_steering) {
		mlx5dr_err(dmn, "SW steering is not supported\n");
		goto uninit_caps;
	}

	/* Allocate resources */
	ret = dr_domain_init_resources(dmn);
	if (ret) {
		mlx5dr_err(dmn, "Failed init domain resources\n");
		goto uninit_caps;
	}

	ret = dr_domain_init_cache(dmn);
	if (ret) {
		mlx5dr_err(dmn, "Failed initialize domain cache\n");
		goto uninit_resourses;
	}

	/* Init CRC table for htbl CRC calculation */
	mlx5dr_crc32_init_table();

	return dmn;

uninit_resourses:
	dr_domain_uninit_resources(dmn);
uninit_caps:
	dr_domain_caps_uninit(dmn);
free_domain:
	kfree(dmn);
	return NULL;
}