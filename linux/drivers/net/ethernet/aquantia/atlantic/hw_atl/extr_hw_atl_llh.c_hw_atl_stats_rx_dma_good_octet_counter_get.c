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
typedef  int /*<<< orphan*/  u64 ;
struct aq_hw_s {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HW_ATL_STATS_RX_DMA_GOOD_OCTET_COUNTERLSW ; 
 int /*<<< orphan*/  aq_hw_read_reg64 (struct aq_hw_s*,int /*<<< orphan*/ ) ; 

u64 hw_atl_stats_rx_dma_good_octet_counter_get(struct aq_hw_s *aq_hw)
{
	return aq_hw_read_reg64(aq_hw, HW_ATL_STATS_RX_DMA_GOOD_OCTET_COUNTERLSW);
}