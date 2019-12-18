#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct page {int dummy; } ;
struct mock_dmabuf {int npages; int /*<<< orphan*/ * pages; } ;
struct dma_buf {int dummy; } ;
struct TYPE_4__ {int size; struct mock_dmabuf* priv; int /*<<< orphan*/  flags; int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_DMA_BUF_EXPORT_INFO (TYPE_1__) ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct dma_buf* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct dma_buf*) ; 
 int /*<<< orphan*/  O_CLOEXEC ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  alloc_page (int /*<<< orphan*/ ) ; 
 struct dma_buf* dma_buf_export (TYPE_1__*) ; 
 TYPE_1__ exp_info ; 
 int /*<<< orphan*/  kfree (struct mock_dmabuf*) ; 
 struct mock_dmabuf* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mock_dmabuf_ops ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct dma_buf *mock_dmabuf(int npages)
{
	struct mock_dmabuf *mock;
	DEFINE_DMA_BUF_EXPORT_INFO(exp_info);
	struct dma_buf *dmabuf;
	int i;

	mock = kmalloc(sizeof(*mock) + npages * sizeof(struct page *),
		       GFP_KERNEL);
	if (!mock)
		return ERR_PTR(-ENOMEM);

	mock->npages = npages;
	for (i = 0; i < npages; i++) {
		mock->pages[i] = alloc_page(GFP_KERNEL);
		if (!mock->pages[i])
			goto err;
	}

	exp_info.ops = &mock_dmabuf_ops;
	exp_info.size = npages * PAGE_SIZE;
	exp_info.flags = O_CLOEXEC;
	exp_info.priv = mock;

	dmabuf = dma_buf_export(&exp_info);
	if (IS_ERR(dmabuf))
		goto err;

	return dmabuf;

err:
	while (i--)
		put_page(mock->pages[i]);
	kfree(mock);
	return ERR_PTR(-ENOMEM);
}