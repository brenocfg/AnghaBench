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
struct aq_hw_s {int dummy; } ;

/* Variables and functions */
 int aq_hw_err_from_flags (struct aq_hw_s*) ; 
 int /*<<< orphan*/  hw_atl_rpb_rx_buff_en_set (struct aq_hw_s*,int) ; 
 int /*<<< orphan*/  hw_atl_tpb_tx_buff_en_set (struct aq_hw_s*,int) ; 

__attribute__((used)) static int hw_atl_a0_hw_start(struct aq_hw_s *self)
{
	hw_atl_tpb_tx_buff_en_set(self, 1);
	hw_atl_rpb_rx_buff_en_set(self, 1);
	return aq_hw_err_from_flags(self);
}