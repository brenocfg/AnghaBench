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
struct ib_sge {int dummy; } ;
struct ib_pd {int dummy; } ;
typedef  enum ib_uverbs_advise_mr_advice { ____Placeholder_ib_uverbs_advise_mr_advice } ib_uverbs_advise_mr_advice ;

/* Variables and functions */
 int EOPNOTSUPP ; 

__attribute__((used)) static inline int
mlx5_ib_advise_mr_prefetch(struct ib_pd *pd,
			   enum ib_uverbs_advise_mr_advice advice, u32 flags,
			   struct ib_sge *sg_list, u32 num_sge)
{
	return -EOPNOTSUPP;
}