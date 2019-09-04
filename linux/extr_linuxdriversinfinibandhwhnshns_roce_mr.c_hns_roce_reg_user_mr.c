#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct ib_udata {int dummy; } ;
struct ib_pd {TYPE_1__* uobject; int /*<<< orphan*/  device; } ;
struct ib_mr {int /*<<< orphan*/  lkey; int /*<<< orphan*/  rkey; } ;
struct hns_roce_mr {int /*<<< orphan*/  umem; struct ib_mr ibmr; int /*<<< orphan*/  key; } ;
struct TYPE_5__ {int pbl_hop_num; int pbl_ba_pg_sz; } ;
struct hns_roce_dev {TYPE_2__ caps; struct device* dev; } ;
struct device {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  pdn; } ;
struct TYPE_4__ {int /*<<< orphan*/  context; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 struct ib_mr* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HNS_ROCE_MAX_MTPT_PBL_NUM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PAGE_SHIFT ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ,...) ; 
 int hns_roce_ib_umem_write_mr (struct hns_roce_dev*,struct hns_roce_mr*,int /*<<< orphan*/ ) ; 
 int hns_roce_mr_alloc (struct hns_roce_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,struct hns_roce_mr*) ; 
 int hns_roce_mr_enable (struct hns_roce_dev*,struct hns_roce_mr*) ; 
 int /*<<< orphan*/  hns_roce_mr_free (struct hns_roce_dev*,struct hns_roce_mr*) ; 
 int /*<<< orphan*/  ib_umem_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int ib_umem_page_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_umem_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct hns_roce_mr*) ; 
 struct hns_roce_mr* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct hns_roce_dev* to_hr_dev (int /*<<< orphan*/ ) ; 
 TYPE_3__* to_hr_pd (struct ib_pd*) ; 

struct ib_mr *hns_roce_reg_user_mr(struct ib_pd *pd, u64 start, u64 length,
				   u64 virt_addr, int access_flags,
				   struct ib_udata *udata)
{
	struct hns_roce_dev *hr_dev = to_hr_dev(pd->device);
	struct device *dev = hr_dev->dev;
	struct hns_roce_mr *mr;
	int bt_size;
	int ret;
	int n;
	int i;

	mr = kmalloc(sizeof(*mr), GFP_KERNEL);
	if (!mr)
		return ERR_PTR(-ENOMEM);

	mr->umem = ib_umem_get(pd->uobject->context, start, length,
			       access_flags, 0);
	if (IS_ERR(mr->umem)) {
		ret = PTR_ERR(mr->umem);
		goto err_free;
	}

	n = ib_umem_page_count(mr->umem);

	if (!hr_dev->caps.pbl_hop_num) {
		if (n > HNS_ROCE_MAX_MTPT_PBL_NUM) {
			dev_err(dev,
			     " MR len %lld err. MR is limited to 4G at most!\n",
			     length);
			ret = -EINVAL;
			goto err_umem;
		}
	} else {
		int pbl_size = 1;

		bt_size = (1 << (hr_dev->caps.pbl_ba_pg_sz + PAGE_SHIFT)) / 8;
		for (i = 0; i < hr_dev->caps.pbl_hop_num; i++)
			pbl_size *= bt_size;
		if (n > pbl_size) {
			dev_err(dev,
			    " MR len %lld err. MR page num is limited to %d!\n",
			    length, pbl_size);
			ret = -EINVAL;
			goto err_umem;
		}
	}

	ret = hns_roce_mr_alloc(hr_dev, to_hr_pd(pd)->pdn, virt_addr, length,
				access_flags, n, mr);
	if (ret)
		goto err_umem;

	ret = hns_roce_ib_umem_write_mr(hr_dev, mr, mr->umem);
	if (ret)
		goto err_mr;

	ret = hns_roce_mr_enable(hr_dev, mr);
	if (ret)
		goto err_mr;

	mr->ibmr.rkey = mr->ibmr.lkey = mr->key;

	return &mr->ibmr;

err_mr:
	hns_roce_mr_free(hr_dev, mr);

err_umem:
	ib_umem_release(mr->umem);

err_free:
	kfree(mr);
	return ERR_PTR(ret);
}