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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct hinic_hwif {int /*<<< orphan*/  attr; } ;

/* Variables and functions */
 int /*<<< orphan*/  COALESC_TIMER ; 
 int EINVAL ; 
 int HINIC_CSR_MSIX_CTRL_ADDR (int /*<<< orphan*/ ) ; 
 int HINIC_MSIX_ATTR_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LLI_CREDIT ; 
 int /*<<< orphan*/  LLI_TIMER ; 
 int /*<<< orphan*/  PENDING_LIMIT ; 
 int /*<<< orphan*/  RESEND_TIMER ; 
 int /*<<< orphan*/  VALID_MSIX_IDX (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hinic_hwif_write_reg (struct hinic_hwif*,int,int) ; 

int hinic_msix_attr_set(struct hinic_hwif *hwif, u16 msix_index,
			u8 pending_limit, u8 coalesc_timer,
			u8 lli_timer, u8 lli_credit_limit,
			u8 resend_timer)
{
	u32 msix_ctrl, addr;

	if (!VALID_MSIX_IDX(&hwif->attr, msix_index))
		return -EINVAL;

	msix_ctrl = HINIC_MSIX_ATTR_SET(pending_limit, PENDING_LIMIT)   |
		    HINIC_MSIX_ATTR_SET(coalesc_timer, COALESC_TIMER)   |
		    HINIC_MSIX_ATTR_SET(lli_timer, LLI_TIMER)           |
		    HINIC_MSIX_ATTR_SET(lli_credit_limit, LLI_CREDIT)   |
		    HINIC_MSIX_ATTR_SET(resend_timer, RESEND_TIMER);

	addr = HINIC_CSR_MSIX_CTRL_ADDR(msix_index);

	hinic_hwif_write_reg(hwif, addr, msix_ctrl);
	return 0;
}