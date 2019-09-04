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
struct mvpp2_port {TYPE_1__* priv; } ;
typedef  int phys_addr_t ;
typedef  int dma_addr_t ;
struct TYPE_2__ {scalar_t__ hw_version; } ;

/* Variables and functions */
 scalar_t__ MVPP22 ; 
 int MVPP22_BM_ADDR_HIGH_PHYS_RLS_MASK ; 
 int /*<<< orphan*/  MVPP22_BM_ADDR_HIGH_RLS_REG ; 
 int MVPP22_BM_ADDR_HIGH_VIRT_RLS_MASK ; 
 int MVPP22_BM_ADDR_HIGH_VIRT_RLS_SHIFT ; 
 int /*<<< orphan*/  MVPP2_BM_PHY_RLS_REG (int) ; 
 int /*<<< orphan*/  MVPP2_BM_VIRT_RLS_REG ; 
 int get_cpu () ; 
 int /*<<< orphan*/  mvpp2_percpu_write_relaxed (TYPE_1__*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_cpu () ; 
 int upper_32_bits (int) ; 

__attribute__((used)) static inline void mvpp2_bm_pool_put(struct mvpp2_port *port, int pool,
				     dma_addr_t buf_dma_addr,
				     phys_addr_t buf_phys_addr)
{
	int cpu = get_cpu();

	if (port->priv->hw_version == MVPP22) {
		u32 val = 0;

		if (sizeof(dma_addr_t) == 8)
			val |= upper_32_bits(buf_dma_addr) &
				MVPP22_BM_ADDR_HIGH_PHYS_RLS_MASK;

		if (sizeof(phys_addr_t) == 8)
			val |= (upper_32_bits(buf_phys_addr)
				<< MVPP22_BM_ADDR_HIGH_VIRT_RLS_SHIFT) &
				MVPP22_BM_ADDR_HIGH_VIRT_RLS_MASK;

		mvpp2_percpu_write_relaxed(port->priv, cpu,
					   MVPP22_BM_ADDR_HIGH_RLS_REG, val);
	}

	/* MVPP2_BM_VIRT_RLS_REG is not interpreted by HW, and simply
	 * returned in the "cookie" field of the RX
	 * descriptor. Instead of storing the virtual address, we
	 * store the physical address
	 */
	mvpp2_percpu_write_relaxed(port->priv, cpu,
				   MVPP2_BM_VIRT_RLS_REG, buf_phys_addr);
	mvpp2_percpu_write_relaxed(port->priv, cpu,
				   MVPP2_BM_PHY_RLS_REG(pool), buf_dma_addr);

	put_cpu();
}