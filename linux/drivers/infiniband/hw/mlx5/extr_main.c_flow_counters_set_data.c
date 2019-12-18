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
struct mlx5_ib_mcounters {int /*<<< orphan*/ * hw_cntrs_hndl; scalar_t__ cntrs_max_index; } ;
struct mlx5_ib_flow_counters_desc {int dummy; } ;
struct mlx5_ib_flow_counters_data {int ncounters; int /*<<< orphan*/  counters_data; } ;
struct mlx5_ib_create_flow {scalar_t__ ncounters_data; struct mlx5_ib_flow_counters_data* data; } ;
struct ib_counters {int /*<<< orphan*/  device; } ;
struct TYPE_2__ {int /*<<< orphan*/  mdev; } ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int MAX_COUNTERS_NUM ; 
 int /*<<< orphan*/  MLX5_IB_COUNTERS_FLOW ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 scalar_t__ copy_from_user (struct mlx5_ib_flow_counters_desc*,int /*<<< orphan*/ ,int) ; 
 int counters_set_description (struct ib_counters*,int /*<<< orphan*/ ,struct mlx5_ib_flow_counters_desc*,int) ; 
 struct mlx5_ib_flow_counters_desc* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mlx5_ib_flow_counters_desc*) ; 
 int /*<<< orphan*/ * mlx5_fc_create (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlx5_fc_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct mlx5_ib_mcounters* to_mcounters (struct ib_counters*) ; 
 TYPE_1__* to_mdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u64_to_user_ptr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int flow_counters_set_data(struct ib_counters *ibcounters,
				  struct mlx5_ib_create_flow *ucmd)
{
	struct mlx5_ib_mcounters *mcounters = to_mcounters(ibcounters);
	struct mlx5_ib_flow_counters_data *cntrs_data = NULL;
	struct mlx5_ib_flow_counters_desc *desc_data = NULL;
	bool hw_hndl = false;
	int ret = 0;

	if (ucmd && ucmd->ncounters_data != 0) {
		cntrs_data = ucmd->data;
		if (cntrs_data->ncounters > MAX_COUNTERS_NUM)
			return -EINVAL;

		desc_data = kcalloc(cntrs_data->ncounters,
				    sizeof(*desc_data),
				    GFP_KERNEL);
		if (!desc_data)
			return  -ENOMEM;

		if (copy_from_user(desc_data,
				   u64_to_user_ptr(cntrs_data->counters_data),
				   sizeof(*desc_data) * cntrs_data->ncounters)) {
			ret = -EFAULT;
			goto free;
		}
	}

	if (!mcounters->hw_cntrs_hndl) {
		mcounters->hw_cntrs_hndl = mlx5_fc_create(
			to_mdev(ibcounters->device)->mdev, false);
		if (IS_ERR(mcounters->hw_cntrs_hndl)) {
			ret = PTR_ERR(mcounters->hw_cntrs_hndl);
			goto free;
		}
		hw_hndl = true;
	}

	if (desc_data) {
		/* counters already bound to at least one flow */
		if (mcounters->cntrs_max_index) {
			ret = -EINVAL;
			goto free_hndl;
		}

		ret = counters_set_description(ibcounters,
					       MLX5_IB_COUNTERS_FLOW,
					       desc_data,
					       cntrs_data->ncounters);
		if (ret)
			goto free_hndl;

	} else if (!mcounters->cntrs_max_index) {
		/* counters not bound yet, must have udata passed */
		ret = -EINVAL;
		goto free_hndl;
	}

	return 0;

free_hndl:
	if (hw_hndl) {
		mlx5_fc_destroy(to_mdev(ibcounters->device)->mdev,
				mcounters->hw_cntrs_hndl);
		mcounters->hw_cntrs_hndl = NULL;
	}
free:
	kfree(desc_data);
	return ret;
}