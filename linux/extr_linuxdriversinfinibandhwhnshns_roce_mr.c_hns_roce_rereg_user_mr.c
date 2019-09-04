#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct ib_udata {int dummy; } ;
struct ib_pd {int dummy; } ;
struct ib_mr {TYPE_1__* uobject; int /*<<< orphan*/  device; } ;
struct hns_roce_mr {int enabled; unsigned long long size; int access; struct hns_roce_cmd_mailbox* umem; int /*<<< orphan*/  pbl_dma_addr; int /*<<< orphan*/  pbl_buf; int /*<<< orphan*/  key; } ;
struct TYPE_7__ {int num_mtpts; scalar_t__ pbl_hop_num; } ;
struct hns_roce_dev {TYPE_3__ caps; TYPE_2__* hw; struct device* dev; } ;
struct hns_roce_cmd_mailbox {int /*<<< orphan*/  buf; int /*<<< orphan*/  dma; } ;
struct device {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  pdn; } ;
struct TYPE_6__ {int (* rereg_write_mtpt ) (struct hns_roce_dev*,struct hns_roce_mr*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  context; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HNS_ROCE_CMD_QUERY_MPT ; 
 int /*<<< orphan*/  HNS_ROCE_CMD_TIMEOUT_MSECS ; 
 int IB_MR_REREG_ACCESS ; 
 int IB_MR_REREG_PD ; 
 int IB_MR_REREG_TRANS ; 
 scalar_t__ IS_ERR (struct hns_roce_cmd_mailbox*) ; 
 int PTR_ERR (struct hns_roce_cmd_mailbox*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int) ; 
 int /*<<< orphan*/  dma_alloc_coherent (struct device*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct hns_roce_cmd_mailbox* hns_roce_alloc_cmd_mailbox (struct hns_roce_dev*) ; 
 int hns_roce_cmd_mbox (struct hns_roce_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hns_roce_free_cmd_mailbox (struct hns_roce_dev*,struct hns_roce_cmd_mailbox*) ; 
 int hns_roce_hw2sw_mpt (struct hns_roce_dev*,int /*<<< orphan*/ *,unsigned long) ; 
 int hns_roce_ib_umem_write_mr (struct hns_roce_dev*,struct hns_roce_mr*,struct hns_roce_cmd_mailbox*) ; 
 int hns_roce_mhop_alloc (struct hns_roce_dev*,int,struct hns_roce_mr*) ; 
 int /*<<< orphan*/  hns_roce_mhop_free (struct hns_roce_dev*,struct hns_roce_mr*) ; 
 int hns_roce_sw2hw_mpt (struct hns_roce_dev*,struct hns_roce_cmd_mailbox*,unsigned long) ; 
 struct hns_roce_cmd_mailbox* ib_umem_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int ib_umem_page_count (struct hns_roce_cmd_mailbox*) ; 
 int /*<<< orphan*/  ib_umem_release (struct hns_roce_cmd_mailbox*) ; 
 int key_to_hw_index (int /*<<< orphan*/ ) ; 
 int stub1 (struct hns_roce_dev*,struct hns_roce_mr*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct hns_roce_dev* to_hr_dev (int /*<<< orphan*/ ) ; 
 struct hns_roce_mr* to_hr_mr (struct ib_mr*) ; 
 TYPE_4__* to_hr_pd (struct ib_pd*) ; 

int hns_roce_rereg_user_mr(struct ib_mr *ibmr, int flags, u64 start, u64 length,
			   u64 virt_addr, int mr_access_flags, struct ib_pd *pd,
			   struct ib_udata *udata)
{
	struct hns_roce_dev *hr_dev = to_hr_dev(ibmr->device);
	struct hns_roce_mr *mr = to_hr_mr(ibmr);
	struct hns_roce_cmd_mailbox *mailbox;
	struct device *dev = hr_dev->dev;
	unsigned long mtpt_idx;
	u32 pdn = 0;
	int npages;
	int ret;

	if (!mr->enabled)
		return -EINVAL;

	mailbox = hns_roce_alloc_cmd_mailbox(hr_dev);
	if (IS_ERR(mailbox))
		return PTR_ERR(mailbox);

	mtpt_idx = key_to_hw_index(mr->key) & (hr_dev->caps.num_mtpts - 1);
	ret = hns_roce_cmd_mbox(hr_dev, 0, mailbox->dma, mtpt_idx, 0,
				HNS_ROCE_CMD_QUERY_MPT,
				HNS_ROCE_CMD_TIMEOUT_MSECS);
	if (ret)
		goto free_cmd_mbox;

	ret = hns_roce_hw2sw_mpt(hr_dev, NULL, mtpt_idx);
	if (ret)
		dev_warn(dev, "HW2SW_MPT failed (%d)\n", ret);

	mr->enabled = 0;

	if (flags & IB_MR_REREG_PD)
		pdn = to_hr_pd(pd)->pdn;

	if (flags & IB_MR_REREG_TRANS) {
		if (mr->size != ~0ULL) {
			npages = ib_umem_page_count(mr->umem);

			if (hr_dev->caps.pbl_hop_num)
				hns_roce_mhop_free(hr_dev, mr);
			else
				dma_free_coherent(dev, npages * 8, mr->pbl_buf,
						  mr->pbl_dma_addr);
		}
		ib_umem_release(mr->umem);

		mr->umem = ib_umem_get(ibmr->uobject->context, start, length,
				       mr_access_flags, 0);
		if (IS_ERR(mr->umem)) {
			ret = PTR_ERR(mr->umem);
			mr->umem = NULL;
			goto free_cmd_mbox;
		}
		npages = ib_umem_page_count(mr->umem);

		if (hr_dev->caps.pbl_hop_num) {
			ret = hns_roce_mhop_alloc(hr_dev, npages, mr);
			if (ret)
				goto release_umem;
		} else {
			mr->pbl_buf = dma_alloc_coherent(dev, npages * 8,
							 &(mr->pbl_dma_addr),
							 GFP_KERNEL);
			if (!mr->pbl_buf) {
				ret = -ENOMEM;
				goto release_umem;
			}
		}
	}

	ret = hr_dev->hw->rereg_write_mtpt(hr_dev, mr, flags, pdn,
					   mr_access_flags, virt_addr,
					   length, mailbox->buf);
	if (ret) {
		if (flags & IB_MR_REREG_TRANS)
			goto release_umem;
		else
			goto free_cmd_mbox;
	}

	if (flags & IB_MR_REREG_TRANS) {
		ret = hns_roce_ib_umem_write_mr(hr_dev, mr, mr->umem);
		if (ret) {
			if (mr->size != ~0ULL) {
				npages = ib_umem_page_count(mr->umem);

				if (hr_dev->caps.pbl_hop_num)
					hns_roce_mhop_free(hr_dev, mr);
				else
					dma_free_coherent(dev, npages * 8,
							  mr->pbl_buf,
							  mr->pbl_dma_addr);
			}

			goto release_umem;
		}
	}

	ret = hns_roce_sw2hw_mpt(hr_dev, mailbox, mtpt_idx);
	if (ret) {
		dev_err(dev, "SW2HW_MPT failed (%d)\n", ret);
		goto release_umem;
	}

	mr->enabled = 1;
	if (flags & IB_MR_REREG_ACCESS)
		mr->access = mr_access_flags;

	hns_roce_free_cmd_mailbox(hr_dev, mailbox);

	return 0;

release_umem:
	ib_umem_release(mr->umem);

free_cmd_mbox:
	hns_roce_free_cmd_mailbox(hr_dev, mailbox);

	return ret;
}