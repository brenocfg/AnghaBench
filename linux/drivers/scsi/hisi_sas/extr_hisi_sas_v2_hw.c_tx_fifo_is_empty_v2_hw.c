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

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  DMA_TX_DFX1 ; 
 int hisi_sas_phy_read32 (struct hisi_hba*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool tx_fifo_is_empty_v2_hw(struct hisi_hba *hisi_hba, int phy_no)
{
	u32 dfx_val;

	dfx_val = hisi_sas_phy_read32(hisi_hba, phy_no, DMA_TX_DFX1);

	if (dfx_val & BIT(16))
		return false;

	return true;
}