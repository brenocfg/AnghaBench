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
typedef  int /*<<< orphan*/  u32 ;
struct aq_hw_s {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HW_ATL_RPF_RSS_REDIR_ADDR_ADR ; 
 int /*<<< orphan*/  HW_ATL_RPF_RSS_REDIR_ADDR_MSK ; 
 int /*<<< orphan*/  HW_ATL_RPF_RSS_REDIR_ADDR_SHIFT ; 
 int /*<<< orphan*/  aq_hw_write_reg_bit (struct aq_hw_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void hw_atl_rpf_rss_redir_tbl_addr_set(struct aq_hw_s *aq_hw,
				       u32 rss_redir_tbl_addr)
{
	aq_hw_write_reg_bit(aq_hw, HW_ATL_RPF_RSS_REDIR_ADDR_ADR,
			    HW_ATL_RPF_RSS_REDIR_ADDR_MSK,
			    HW_ATL_RPF_RSS_REDIR_ADDR_SHIFT,
			    rss_redir_tbl_addr);
}