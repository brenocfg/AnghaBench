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
 int AQ_NIC_FC_RX ; 
 int /*<<< orphan*/  hw_atl_rpb_rx_xoff_en_per_tc_set (struct aq_hw_s*,int,int) ; 

__attribute__((used)) static int hw_atl_b0_set_fc(struct aq_hw_s *self, u32 fc, u32 tc)
{
	hw_atl_rpb_rx_xoff_en_per_tc_set(self, !!(fc & AQ_NIC_FC_RX), tc);
	return 0;
}