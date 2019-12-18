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
typedef  int u64 ;
struct hns_roce_mtr {int /*<<< orphan*/  hem_list; } ;
struct hns_roce_dev {scalar_t__ hw_rev; } ;
struct hns_roce_buf_region {int offset; int count; } ;
typedef  int dma_addr_t ;

/* Variables and functions */
 int ENOBUFS ; 
 scalar_t__ HNS_ROCE_HW_VER1 ; 
 int PAGE_ADDR_SHIFT ; 
 int* hns_roce_hem_list_find_mtt (struct hns_roce_dev*,int /*<<< orphan*/ *,int,int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hns_roce_write_mtr(struct hns_roce_dev *hr_dev,
			      struct hns_roce_mtr *mtr, dma_addr_t *bufs,
			      struct hns_roce_buf_region *r)
{
	int offset;
	int count;
	int npage;
	u64 *mtts;
	int end;
	int i;

	offset = r->offset;
	end = offset + r->count;
	npage = 0;
	while (offset < end) {
		mtts = hns_roce_hem_list_find_mtt(hr_dev, &mtr->hem_list,
						  offset, &count, NULL);
		if (!mtts)
			return -ENOBUFS;

		/* Save page addr, low 12 bits : 0 */
		for (i = 0; i < count; i++) {
			if (hr_dev->hw_rev == HNS_ROCE_HW_VER1)
				mtts[i] = bufs[npage] >> PAGE_ADDR_SHIFT;
			else
				mtts[i] = bufs[npage];

			npage++;
		}
		offset += count;
	}

	return 0;
}