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
typedef  int u32 ;
struct hns_roce_dev {struct device* dev; } ;
struct TYPE_3__ {int map; void* buf; } ;
struct hns_roce_buf {int nbufs; int npages; int page_shift; TYPE_2__* page_list; TYPE_1__ direct; } ;
struct device {int dummy; } ;
typedef  int dma_addr_t ;
struct TYPE_4__ {int map; void* buf; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PAGE_SHIFT ; 
 void* dma_alloc_coherent (struct device*,int,int*,int /*<<< orphan*/ ) ; 
 int get_order (int) ; 
 int /*<<< orphan*/  hns_roce_buf_free (struct hns_roce_dev*,int,struct hns_roce_buf*) ; 
 TYPE_2__* kcalloc (int,int,int /*<<< orphan*/ ) ; 

int hns_roce_buf_alloc(struct hns_roce_dev *hr_dev, u32 size, u32 max_direct,
		       struct hns_roce_buf *buf, u32 page_shift)
{
	int i = 0;
	dma_addr_t t;
	struct device *dev = hr_dev->dev;
	u32 page_size = 1 << page_shift;
	u32 order;

	/* SQ/RQ buf lease than one page, SQ + RQ = 8K */
	if (size <= max_direct) {
		buf->nbufs = 1;
		/* Npages calculated by page_size */
		order = get_order(size);
		if (order <= page_shift - PAGE_SHIFT)
			order = 0;
		else
			order -= page_shift - PAGE_SHIFT;
		buf->npages = 1 << order;
		buf->page_shift = page_shift;
		/* MTT PA must be recorded in 4k alignment, t is 4k aligned */
		buf->direct.buf = dma_alloc_coherent(dev, size, &t,
						     GFP_KERNEL);
		if (!buf->direct.buf)
			return -ENOMEM;

		buf->direct.map = t;

		while (t & ((1 << buf->page_shift) - 1)) {
			--buf->page_shift;
			buf->npages *= 2;
		}
	} else {
		buf->nbufs = (size + page_size - 1) / page_size;
		buf->npages = buf->nbufs;
		buf->page_shift = page_shift;
		buf->page_list = kcalloc(buf->nbufs, sizeof(*buf->page_list),
					 GFP_KERNEL);

		if (!buf->page_list)
			return -ENOMEM;

		for (i = 0; i < buf->nbufs; ++i) {
			buf->page_list[i].buf = dma_alloc_coherent(dev,
								   page_size,
								   &t,
								   GFP_KERNEL);

			if (!buf->page_list[i].buf)
				goto err_free;

			buf->page_list[i].map = t;
		}
	}

	return 0;

err_free:
	hns_roce_buf_free(hr_dev, size, buf);
	return -ENOMEM;
}