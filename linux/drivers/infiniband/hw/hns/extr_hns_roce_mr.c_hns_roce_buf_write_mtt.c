#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  size_t u32 ;
struct hns_roce_mtt {int dummy; } ;
struct hns_roce_dev {int dummy; } ;
struct TYPE_3__ {scalar_t__ map; } ;
struct hns_roce_buf {size_t npages; int nbufs; size_t page_shift; TYPE_2__* page_list; TYPE_1__ direct; } ;
struct TYPE_4__ {scalar_t__ map; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int hns_roce_write_mtt (struct hns_roce_dev*,struct hns_roce_mtt*,int /*<<< orphan*/ ,size_t,scalar_t__*) ; 
 int /*<<< orphan*/  kfree (scalar_t__*) ; 
 scalar_t__* kmalloc_array (size_t,int,int /*<<< orphan*/ ) ; 

int hns_roce_buf_write_mtt(struct hns_roce_dev *hr_dev,
			   struct hns_roce_mtt *mtt, struct hns_roce_buf *buf)
{
	u64 *page_list;
	int ret;
	u32 i;

	page_list = kmalloc_array(buf->npages, sizeof(*page_list), GFP_KERNEL);
	if (!page_list)
		return -ENOMEM;

	for (i = 0; i < buf->npages; ++i) {
		if (buf->nbufs == 1)
			page_list[i] = buf->direct.map + (i << buf->page_shift);
		else
			page_list[i] = buf->page_list[i].map;

	}
	ret = hns_roce_write_mtt(hr_dev, mtt, 0, buf->npages, page_list);

	kfree(page_list);

	return ret;
}