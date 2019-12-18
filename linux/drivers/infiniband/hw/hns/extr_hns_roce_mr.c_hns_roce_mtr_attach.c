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
struct hns_roce_mtr {int /*<<< orphan*/  hem_list; } ;
struct hns_roce_dev {int /*<<< orphan*/  dev; } ;
struct hns_roce_buf_region {int /*<<< orphan*/  offset; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hns_roce_hem_list_release (struct hns_roce_dev*,int /*<<< orphan*/ *) ; 
 int hns_roce_hem_list_request (struct hns_roce_dev*,int /*<<< orphan*/ *,struct hns_roce_buf_region*,int) ; 
 int hns_roce_write_mtr (struct hns_roce_dev*,struct hns_roce_mtr*,int /*<<< orphan*/ *,struct hns_roce_buf_region*) ; 

int hns_roce_mtr_attach(struct hns_roce_dev *hr_dev, struct hns_roce_mtr *mtr,
			dma_addr_t **bufs, struct hns_roce_buf_region *regions,
			int region_cnt)
{
	struct hns_roce_buf_region *r;
	int ret;
	int i;

	ret = hns_roce_hem_list_request(hr_dev, &mtr->hem_list, regions,
					region_cnt);
	if (ret)
		return ret;

	for (i = 0; i < region_cnt; i++) {
		r = &regions[i];
		ret = hns_roce_write_mtr(hr_dev, mtr, bufs[i], r);
		if (ret) {
			dev_err(hr_dev->dev,
				"write mtr[%d/%d] err %d,offset=%d.\n",
				i, region_cnt, ret,  r->offset);
			goto err_write;
		}
	}

	return 0;

err_write:
	hns_roce_hem_list_release(hr_dev, &mtr->hem_list);

	return ret;
}