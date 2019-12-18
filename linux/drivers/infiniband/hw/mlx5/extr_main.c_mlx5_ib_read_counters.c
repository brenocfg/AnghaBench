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
typedef  int /*<<< orphan*/  u64 ;
struct uverbs_attr_bundle {int dummy; } ;
struct mlx5_read_counters_attr {scalar_t__* out; int /*<<< orphan*/  flags; int /*<<< orphan*/  hw_cntrs_hndl; } ;
struct mlx5_ib_mcounters {scalar_t__ cntrs_max_index; int (* read_counters ) (int /*<<< orphan*/ ,struct mlx5_read_counters_attr*) ;int ncounters; int /*<<< orphan*/  mcntrs_mutex; struct mlx5_ib_flow_counters_desc* counters_data; int /*<<< orphan*/  hw_cntrs_hndl; int /*<<< orphan*/  counters_num; } ;
struct mlx5_ib_flow_counters_desc {size_t index; size_t description; } ;
struct ib_counters_read_attr {scalar_t__ ncounters; int /*<<< orphan*/ * counters_buff; int /*<<< orphan*/  flags; } ;
struct ib_counters {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__* kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (scalar_t__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (int /*<<< orphan*/ ,struct mlx5_read_counters_attr*) ; 
 struct mlx5_ib_mcounters* to_mcounters (struct ib_counters*) ; 

__attribute__((used)) static int mlx5_ib_read_counters(struct ib_counters *counters,
				 struct ib_counters_read_attr *read_attr,
				 struct uverbs_attr_bundle *attrs)
{
	struct mlx5_ib_mcounters *mcounters = to_mcounters(counters);
	struct mlx5_read_counters_attr mread_attr = {};
	struct mlx5_ib_flow_counters_desc *desc;
	int ret, i;

	mutex_lock(&mcounters->mcntrs_mutex);
	if (mcounters->cntrs_max_index > read_attr->ncounters) {
		ret = -EINVAL;
		goto err_bound;
	}

	mread_attr.out = kcalloc(mcounters->counters_num, sizeof(u64),
				 GFP_KERNEL);
	if (!mread_attr.out) {
		ret = -ENOMEM;
		goto err_bound;
	}

	mread_attr.hw_cntrs_hndl = mcounters->hw_cntrs_hndl;
	mread_attr.flags = read_attr->flags;
	ret = mcounters->read_counters(counters->device, &mread_attr);
	if (ret)
		goto err_read;

	/* do the pass over the counters data array to assign according to the
	 * descriptions and indexing pairs
	 */
	desc = mcounters->counters_data;
	for (i = 0; i < mcounters->ncounters; i++)
		read_attr->counters_buff[desc[i].index] += mread_attr.out[desc[i].description];

err_read:
	kfree(mread_attr.out);
err_bound:
	mutex_unlock(&mcounters->mcntrs_mutex);
	return ret;
}