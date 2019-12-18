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
struct ib_pd {int /*<<< orphan*/  device; } ;
struct ib_mr {int /*<<< orphan*/  lkey; int /*<<< orphan*/  rkey; } ;
struct hns_roce_mr {struct ib_mr ibmr; int /*<<< orphan*/ * umem; int /*<<< orphan*/  key; int /*<<< orphan*/  type; } ;
struct TYPE_2__ {int /*<<< orphan*/  pdn; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct ib_mr* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MR_TYPE_DMA ; 
 int hns_roce_mr_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long long,int,int /*<<< orphan*/ ,struct hns_roce_mr*) ; 
 int hns_roce_mr_enable (int /*<<< orphan*/ ,struct hns_roce_mr*) ; 
 int /*<<< orphan*/  hns_roce_mr_free (int /*<<< orphan*/ ,struct hns_roce_mr*) ; 
 int /*<<< orphan*/  kfree (struct hns_roce_mr*) ; 
 struct hns_roce_mr* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_hr_dev (int /*<<< orphan*/ ) ; 
 TYPE_1__* to_hr_pd (struct ib_pd*) ; 

struct ib_mr *hns_roce_get_dma_mr(struct ib_pd *pd, int acc)
{
	struct hns_roce_mr *mr;
	int ret;

	mr = kmalloc(sizeof(*mr), GFP_KERNEL);
	if (mr == NULL)
		return  ERR_PTR(-ENOMEM);

	mr->type = MR_TYPE_DMA;

	/* Allocate memory region key */
	ret = hns_roce_mr_alloc(to_hr_dev(pd->device), to_hr_pd(pd)->pdn, 0,
				~0ULL, acc, 0, mr);
	if (ret)
		goto err_free;

	ret = hns_roce_mr_enable(to_hr_dev(pd->device), mr);
	if (ret)
		goto err_mr;

	mr->ibmr.rkey = mr->ibmr.lkey = mr->key;
	mr->umem = NULL;

	return &mr->ibmr;

err_mr:
	hns_roce_mr_free(to_hr_dev(pd->device), mr);

err_free:
	kfree(mr);
	return ERR_PTR(ret);
}