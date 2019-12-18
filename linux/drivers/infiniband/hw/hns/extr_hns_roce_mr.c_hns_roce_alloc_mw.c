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
struct ib_udata {int dummy; } ;
struct ib_pd {int /*<<< orphan*/  device; } ;
struct ib_mw {int type; int /*<<< orphan*/  rkey; } ;
struct hns_roce_mw {struct ib_mw ibmw; int /*<<< orphan*/  pbl_buf_pg_sz; int /*<<< orphan*/  pbl_ba_pg_sz; int /*<<< orphan*/  pbl_hop_num; int /*<<< orphan*/  pdn; int /*<<< orphan*/  rkey; } ;
struct TYPE_5__ {int /*<<< orphan*/  pbl_buf_pg_sz; int /*<<< orphan*/  pbl_ba_pg_sz; int /*<<< orphan*/  pbl_hop_num; } ;
struct TYPE_4__ {int /*<<< orphan*/  mtpt_bitmap; } ;
struct hns_roce_dev {TYPE_2__ caps; TYPE_1__ mr_table; } ;
typedef  enum ib_mw_type { ____Placeholder_ib_mw_type } ib_mw_type ;
struct TYPE_6__ {int /*<<< orphan*/  pdn; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct ib_mw* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int hns_roce_bitmap_alloc (int /*<<< orphan*/ *,unsigned long*) ; 
 int hns_roce_mw_enable (struct hns_roce_dev*,struct hns_roce_mw*) ; 
 int /*<<< orphan*/  hns_roce_mw_free (struct hns_roce_dev*,struct hns_roce_mw*) ; 
 int /*<<< orphan*/  hw_index_to_key (unsigned long) ; 
 int /*<<< orphan*/  kfree (struct hns_roce_mw*) ; 
 struct hns_roce_mw* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct hns_roce_dev* to_hr_dev (int /*<<< orphan*/ ) ; 
 TYPE_3__* to_hr_pd (struct ib_pd*) ; 

struct ib_mw *hns_roce_alloc_mw(struct ib_pd *ib_pd, enum ib_mw_type type,
				struct ib_udata *udata)
{
	struct hns_roce_dev *hr_dev = to_hr_dev(ib_pd->device);
	struct hns_roce_mw *mw;
	unsigned long index = 0;
	int ret;

	mw = kmalloc(sizeof(*mw), GFP_KERNEL);
	if (!mw)
		return ERR_PTR(-ENOMEM);

	/* Allocate a key for mw from bitmap */
	ret = hns_roce_bitmap_alloc(&hr_dev->mr_table.mtpt_bitmap, &index);
	if (ret)
		goto err_bitmap;

	mw->rkey = hw_index_to_key(index);

	mw->ibmw.rkey = mw->rkey;
	mw->ibmw.type = type;
	mw->pdn = to_hr_pd(ib_pd)->pdn;
	mw->pbl_hop_num = hr_dev->caps.pbl_hop_num;
	mw->pbl_ba_pg_sz = hr_dev->caps.pbl_ba_pg_sz;
	mw->pbl_buf_pg_sz = hr_dev->caps.pbl_buf_pg_sz;

	ret = hns_roce_mw_enable(hr_dev, mw);
	if (ret)
		goto err_mw;

	return &mw->ibmw;

err_mw:
	hns_roce_mw_free(hr_dev, mw);

err_bitmap:
	kfree(mw);

	return ERR_PTR(ret);
}