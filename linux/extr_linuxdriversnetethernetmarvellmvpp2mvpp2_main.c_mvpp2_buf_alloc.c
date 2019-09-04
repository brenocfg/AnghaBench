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
struct mvpp2_port {TYPE_2__* dev; } ;
struct mvpp2_bm_pool {int /*<<< orphan*/  pkt_size; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  MVPP2_RX_BUF_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* mvpp2_frag_alloc (struct mvpp2_bm_pool*) ; 
 int /*<<< orphan*/  mvpp2_frag_free (struct mvpp2_bm_pool*,void*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virt_to_phys (void*) ; 

__attribute__((used)) static void *mvpp2_buf_alloc(struct mvpp2_port *port,
			     struct mvpp2_bm_pool *bm_pool,
			     dma_addr_t *buf_dma_addr,
			     phys_addr_t *buf_phys_addr,
			     gfp_t gfp_mask)
{
	dma_addr_t dma_addr;
	void *data;

	data = mvpp2_frag_alloc(bm_pool);
	if (!data)
		return NULL;

	dma_addr = dma_map_single(port->dev->dev.parent, data,
				  MVPP2_RX_BUF_SIZE(bm_pool->pkt_size),
				  DMA_FROM_DEVICE);
	if (unlikely(dma_mapping_error(port->dev->dev.parent, dma_addr))) {
		mvpp2_frag_free(bm_pool, data);
		return NULL;
	}
	*buf_dma_addr = dma_addr;
	*buf_phys_addr = virt_to_phys(data);

	return data;
}