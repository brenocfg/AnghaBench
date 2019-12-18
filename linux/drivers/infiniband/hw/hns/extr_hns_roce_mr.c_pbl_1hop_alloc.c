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
typedef  int u32 ;
struct hns_roce_mr {int pbl_size; int pbl_hop_num; int /*<<< orphan*/  pbl_buf_pg_sz; int /*<<< orphan*/  pbl_ba_pg_sz; int /*<<< orphan*/  pbl_dma_addr; int /*<<< orphan*/  pbl_ba; int /*<<< orphan*/  pbl_buf; } ;
struct TYPE_2__ {int /*<<< orphan*/  pbl_buf_pg_sz; int /*<<< orphan*/  pbl_ba_pg_sz; } ;
struct hns_roce_dev {TYPE_1__ caps; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  dma_alloc_coherent (struct device*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pbl_1hop_alloc(struct hns_roce_dev *hr_dev, int npages,
			       struct hns_roce_mr *mr, u32 pbl_bt_sz)
{
	struct device *dev = hr_dev->dev;

	if (npages > pbl_bt_sz / 8) {
		dev_err(dev, "npages %d is larger than buf_pg_sz!",
			npages);
		return -EINVAL;
	}
	mr->pbl_buf = dma_alloc_coherent(dev, npages * 8,
					 &(mr->pbl_dma_addr),
					 GFP_KERNEL);
	if (!mr->pbl_buf)
		return -ENOMEM;

	mr->pbl_size = npages;
	mr->pbl_ba = mr->pbl_dma_addr;
	mr->pbl_hop_num = 1;
	mr->pbl_ba_pg_sz = hr_dev->caps.pbl_ba_pg_sz;
	mr->pbl_buf_pg_sz = hr_dev->caps.pbl_buf_pg_sz;
	return 0;

}