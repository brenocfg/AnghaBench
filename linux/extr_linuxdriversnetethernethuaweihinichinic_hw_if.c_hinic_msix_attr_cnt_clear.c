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
typedef  int /*<<< orphan*/  u16 ;
struct hinic_hwif {int /*<<< orphan*/  attr; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HINIC_CSR_MSIX_CNT_ADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HINIC_MSIX_CNT_SET (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RESEND_TIMER ; 
 int /*<<< orphan*/  VALID_MSIX_IDX (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hinic_hwif_write_reg (struct hinic_hwif*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int hinic_msix_attr_cnt_clear(struct hinic_hwif *hwif, u16 msix_index)
{
	u32 msix_ctrl, addr;

	if (!VALID_MSIX_IDX(&hwif->attr, msix_index))
		return -EINVAL;

	msix_ctrl = HINIC_MSIX_CNT_SET(1, RESEND_TIMER);
	addr = HINIC_CSR_MSIX_CNT_ADDR(msix_index);

	hinic_hwif_write_reg(hwif, addr, msix_ctrl);
	return 0;
}