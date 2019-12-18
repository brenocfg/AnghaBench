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
struct dw_mci_slot {struct dw_mci* host; } ;
struct dw_mci {int verid; } ;

/* Variables and functions */
 int dw_mci_zx_emmc_execute_tuning (struct dw_mci_slot*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dw_mci_zx_execute_tuning(struct dw_mci_slot *slot, u32 opcode)
{
	struct dw_mci *host = slot->host;

	if (host->verid == 0x290a) /* only for emmc */
		return dw_mci_zx_emmc_execute_tuning(slot, opcode);
	/* TODO: Add 0x210a dedicated tuning for sd/sdio */

	return 0;
}