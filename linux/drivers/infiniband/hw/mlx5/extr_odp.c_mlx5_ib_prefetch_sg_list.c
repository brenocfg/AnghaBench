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
typedef  size_t u32 ;
struct mlx5_ib_dev {int dummy; } ;
struct ib_sge {int /*<<< orphan*/  length; int /*<<< orphan*/  addr; int /*<<< orphan*/  lkey; } ;
struct ib_pd {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int pagefault_single_data_segment (struct mlx5_ib_dev*,struct ib_pd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *,size_t) ; 
 struct mlx5_ib_dev* to_mdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlx5_ib_prefetch_sg_list(struct ib_pd *pd, u32 pf_flags,
				    struct ib_sge *sg_list, u32 num_sge)
{
	u32 i;
	int ret = 0;
	struct mlx5_ib_dev *dev = to_mdev(pd->device);

	for (i = 0; i < num_sge; ++i) {
		struct ib_sge *sg = &sg_list[i];
		int bytes_committed = 0;

		ret = pagefault_single_data_segment(dev, pd, sg->lkey, sg->addr,
						    sg->length,
						    &bytes_committed, NULL,
						    pf_flags);
		if (ret < 0)
			break;
	}

	return ret < 0 ? ret : 0;
}