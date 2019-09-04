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
struct mvpp2_port {int dummy; } ;
struct mvpp2_bm_pool {int dummy; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  mvpp2_bm_pool_put (struct mvpp2_port*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* mvpp2_buf_alloc (struct mvpp2_port*,struct mvpp2_bm_pool*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mvpp2_rx_refill(struct mvpp2_port *port,
			   struct mvpp2_bm_pool *bm_pool, int pool)
{
	dma_addr_t dma_addr;
	phys_addr_t phys_addr;
	void *buf;

	/* No recycle or too many buffers are in use, so allocate a new skb */
	buf = mvpp2_buf_alloc(port, bm_pool, &dma_addr, &phys_addr,
			      GFP_ATOMIC);
	if (!buf)
		return -ENOMEM;

	mvpp2_bm_pool_put(port, pool, dma_addr, phys_addr);

	return 0;
}