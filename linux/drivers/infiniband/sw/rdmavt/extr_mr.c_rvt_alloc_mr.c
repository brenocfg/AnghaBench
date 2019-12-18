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
struct ib_mr {int dummy; } ;
struct rvt_mr {struct ib_mr ibmr; } ;
struct ib_udata {int dummy; } ;
struct ib_pd {int dummy; } ;
typedef  enum ib_mr_type { ____Placeholder_ib_mr_type } ib_mr_type ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct ib_mr* ERR_PTR (int /*<<< orphan*/ ) ; 
 int IB_MR_TYPE_MEM_REG ; 
 scalar_t__ IS_ERR (struct rvt_mr*) ; 
 struct rvt_mr* __rvt_alloc_mr (int /*<<< orphan*/ ,struct ib_pd*) ; 

struct ib_mr *rvt_alloc_mr(struct ib_pd *pd, enum ib_mr_type mr_type,
			   u32 max_num_sg, struct ib_udata *udata)
{
	struct rvt_mr *mr;

	if (mr_type != IB_MR_TYPE_MEM_REG)
		return ERR_PTR(-EINVAL);

	mr = __rvt_alloc_mr(max_num_sg, pd);
	if (IS_ERR(mr))
		return (struct ib_mr *)mr;

	return &mr->ibmr;
}