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
 int /*<<< orphan*/  aq_hw_write_reg_bit (struct aq_hw_s*,int,int,int,int) ; 

void hw_atl_rpf_rpb_user_priority_tc_map_set(struct aq_hw_s *aq_hw,
					     u32 user_priority_tc_map, u32 tc)
{
/* register address for bitfield rx_tc_up{t}[2:0] */
	static u32 rpf_rpb_rx_tc_upt_adr[8] = {
			0x000054c4U, 0x000054C4U, 0x000054C4U, 0x000054C4U,
			0x000054c4U, 0x000054C4U, 0x000054C4U, 0x000054C4U
		};

/* bitmask for bitfield rx_tc_up{t}[2:0] */
	static u32 rpf_rpb_rx_tc_upt_msk[8] = {
			0x00000007U, 0x00000070U, 0x00000700U, 0x00007000U,
			0x00070000U, 0x00700000U, 0x07000000U, 0x70000000U
		};

/* lower bit position of bitfield rx_tc_up{t}[2:0] */
	static u32 rpf_rpb_rx_tc_upt_shft[8] = {
			0U, 4U, 8U, 12U, 16U, 20U, 24U, 28U
		};

	aq_hw_write_reg_bit(aq_hw, rpf_rpb_rx_tc_upt_adr[tc],
			    rpf_rpb_rx_tc_upt_msk[tc],
			    rpf_rpb_rx_tc_upt_shft[tc],
			    user_priority_tc_map);
}