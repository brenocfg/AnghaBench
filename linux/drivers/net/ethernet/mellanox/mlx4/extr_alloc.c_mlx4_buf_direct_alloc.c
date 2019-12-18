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
struct mlx4_dev {TYPE_2__* persist; } ;
struct TYPE_6__ {int map; int /*<<< orphan*/  buf; } ;
struct mlx4_buf {int nbufs; int npages; int page_shift; TYPE_3__ direct; } ;
typedef  int dma_addr_t ;
struct TYPE_5__ {TYPE_1__* pdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ *,int,int*,int /*<<< orphan*/ ) ; 
 int get_order (int) ; 

__attribute__((used)) static int mlx4_buf_direct_alloc(struct mlx4_dev *dev, int size,
				 struct mlx4_buf *buf)
{
	dma_addr_t t;

	buf->nbufs        = 1;
	buf->npages       = 1;
	buf->page_shift   = get_order(size) + PAGE_SHIFT;
	buf->direct.buf   =
		dma_alloc_coherent(&dev->persist->pdev->dev, size, &t,
				   GFP_KERNEL);
	if (!buf->direct.buf)
		return -ENOMEM;

	buf->direct.map = t;

	while (t & ((1 << buf->page_shift) - 1)) {
		--buf->page_shift;
		buf->npages *= 2;
	}

	return 0;
}