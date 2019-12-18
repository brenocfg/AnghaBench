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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct aq_hw_s {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HW_ATL_RPF_L3_DSTA_ADR (scalar_t__) ; 
 int /*<<< orphan*/  aq_hw_write_reg (struct aq_hw_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void hw_atl_rpfl3l4_ipv6_dest_addr_set(struct aq_hw_s *aq_hw, u8 location,
				       u32 *ipv6_dest)
{
	int i;

	for (i = 0; i < 4; ++i)
		aq_hw_write_reg(aq_hw,
				HW_ATL_RPF_L3_DSTA_ADR(location + i),
				ipv6_dest[i]);
}