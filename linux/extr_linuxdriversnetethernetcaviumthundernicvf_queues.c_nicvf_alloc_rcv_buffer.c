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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct rbdr {scalar_t__ is_xdp; } ;
struct pgcache {scalar_t__ dma_addr; int /*<<< orphan*/ * page; } ;
struct nicvf {scalar_t__ rb_page_offset; int /*<<< orphan*/ * rb_page; TYPE_3__* pdev; TYPE_2__* pnicvf; int /*<<< orphan*/  rb_pageref; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {TYPE_1__* drv_stats; } ;
struct TYPE_4__ {int /*<<< orphan*/  rcv_buffer_alloc_failures; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_ATTR_SKIP_CPU_SYNC ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int ENOMEM ; 
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ XDP_PACKET_HEADROOM ; 
 int /*<<< orphan*/  __free_pages (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_map_page_attrs (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct pgcache* nicvf_alloc_page (struct nicvf*,struct rbdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nicvf_get_page (struct nicvf*) ; 
 int /*<<< orphan*/  this_cpu_inc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int nicvf_alloc_rcv_buffer(struct nicvf *nic, struct rbdr *rbdr,
					 gfp_t gfp, u32 buf_len, u64 *rbuf)
{
	struct pgcache *pgcache = NULL;

	/* Check if request can be accomodated in previous allocated page.
	 * But in XDP mode only one buffer per page is permitted.
	 */
	if (!rbdr->is_xdp && nic->rb_page &&
	    ((nic->rb_page_offset + buf_len) <= PAGE_SIZE)) {
		nic->rb_pageref++;
		goto ret;
	}

	nicvf_get_page(nic);
	nic->rb_page = NULL;

	/* Get new page, either recycled or new one */
	pgcache = nicvf_alloc_page(nic, rbdr, gfp);
	if (!pgcache && !nic->rb_page) {
		this_cpu_inc(nic->pnicvf->drv_stats->rcv_buffer_alloc_failures);
		return -ENOMEM;
	}

	nic->rb_page_offset = 0;

	/* Reserve space for header modifications by BPF program */
	if (rbdr->is_xdp)
		buf_len += XDP_PACKET_HEADROOM;

	/* Check if it's recycled */
	if (pgcache)
		nic->rb_page = pgcache->page;
ret:
	if (rbdr->is_xdp && pgcache && pgcache->dma_addr) {
		*rbuf = pgcache->dma_addr;
	} else {
		/* HW will ensure data coherency, CPU sync not required */
		*rbuf = (u64)dma_map_page_attrs(&nic->pdev->dev, nic->rb_page,
						nic->rb_page_offset, buf_len,
						DMA_FROM_DEVICE,
						DMA_ATTR_SKIP_CPU_SYNC);
		if (dma_mapping_error(&nic->pdev->dev, (dma_addr_t)*rbuf)) {
			if (!nic->rb_page_offset)
				__free_pages(nic->rb_page, 0);
			nic->rb_page = NULL;
			return -ENOMEM;
		}
		if (pgcache)
			pgcache->dma_addr = *rbuf + XDP_PACKET_HEADROOM;
		nic->rb_page_offset += buf_len;
	}

	return 0;
}