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
struct hisi_hba {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHNL_INT_STATUS ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  handle_chl_int0_v3_hw (struct hisi_hba*,int) ; 
 int /*<<< orphan*/  handle_chl_int1_v3_hw (struct hisi_hba*,int) ; 
 int /*<<< orphan*/  handle_chl_int2_v3_hw (struct hisi_hba*,int) ; 
 int hisi_sas_read32 (struct hisi_hba*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t int_chnl_int_v3_hw(int irq_no, void *p)
{
	struct hisi_hba *hisi_hba = p;
	u32 irq_msk;
	int phy_no = 0;

	irq_msk = hisi_sas_read32(hisi_hba, CHNL_INT_STATUS)
				& 0xeeeeeeee;

	while (irq_msk) {
		if (irq_msk & (2 << (phy_no * 4)))
			handle_chl_int0_v3_hw(hisi_hba, phy_no);

		if (irq_msk & (4 << (phy_no * 4)))
			handle_chl_int1_v3_hw(hisi_hba, phy_no);

		if (irq_msk & (8 << (phy_no * 4)))
			handle_chl_int2_v3_hw(hisi_hba, phy_no);

		irq_msk &= ~(0xe << (phy_no * 4));
		phy_no++;
	}

	return IRQ_HANDLED;
}