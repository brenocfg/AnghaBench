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
typedef  int u32 ;
struct aq_hw_s {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HW_ATL_B0_INT_MASK ; 
 int aq_hw_err_from_flags (struct aq_hw_s*) ; 
 int /*<<< orphan*/  hw_atl_b0_hw_irq_disable (struct aq_hw_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_atl_rdm_rx_dma_desc_cache_init_done_get ; 
 int /*<<< orphan*/  hw_atl_rdm_rx_dma_desc_cache_init_tgl (struct aq_hw_s*) ; 
 int /*<<< orphan*/  readx_poll_timeout_atomic (int /*<<< orphan*/ ,struct aq_hw_s*,int,int,unsigned int,unsigned int) ; 

__attribute__((used)) static int hw_atl_b0_hw_stop(struct aq_hw_s *self)
{
	int err;
	u32 val;

	hw_atl_b0_hw_irq_disable(self, HW_ATL_B0_INT_MASK);

	/* Invalidate Descriptor Cache to prevent writing to the cached
	 * descriptors and to the data pointer of those descriptors
	 */
	hw_atl_rdm_rx_dma_desc_cache_init_tgl(self);

	err = aq_hw_err_from_flags(self);

	if (err)
		goto err_exit;

	readx_poll_timeout_atomic(hw_atl_rdm_rx_dma_desc_cache_init_done_get,
				  self, val, val == 1, 1000U, 10000U);

err_exit:
	return err;
}