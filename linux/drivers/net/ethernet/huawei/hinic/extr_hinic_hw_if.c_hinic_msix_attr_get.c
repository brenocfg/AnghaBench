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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct hinic_hwif {int /*<<< orphan*/  attr; } ;

/* Variables and functions */
 int /*<<< orphan*/  COALESC_TIMER ; 
 int EINVAL ; 
 int /*<<< orphan*/  HINIC_CSR_MSIX_CTRL_ADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HINIC_MSIX_ATTR_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LLI_CREDIT ; 
 int /*<<< orphan*/  LLI_TIMER ; 
 int /*<<< orphan*/  PENDING_LIMIT ; 
 int /*<<< orphan*/  RESEND_TIMER ; 
 int /*<<< orphan*/  VALID_MSIX_IDX (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hinic_hwif_read_reg (struct hinic_hwif*,int /*<<< orphan*/ ) ; 

int hinic_msix_attr_get(struct hinic_hwif *hwif, u16 msix_index,
			u8 *pending_limit, u8 *coalesc_timer,
			u8 *lli_timer, u8 *lli_credit_limit,
			u8 *resend_timer)
{
	u32 addr, val;

	if (!VALID_MSIX_IDX(&hwif->attr, msix_index))
		return -EINVAL;

	addr = HINIC_CSR_MSIX_CTRL_ADDR(msix_index);
	val  = hinic_hwif_read_reg(hwif, addr);

	*pending_limit    = HINIC_MSIX_ATTR_GET(val, PENDING_LIMIT);
	*coalesc_timer    = HINIC_MSIX_ATTR_GET(val, COALESC_TIMER);
	*lli_timer        = HINIC_MSIX_ATTR_GET(val, LLI_TIMER);
	*lli_credit_limit = HINIC_MSIX_ATTR_GET(val, LLI_CREDIT);
	*resend_timer     = HINIC_MSIX_ATTR_GET(val, RESEND_TIMER);
	return 0;
}