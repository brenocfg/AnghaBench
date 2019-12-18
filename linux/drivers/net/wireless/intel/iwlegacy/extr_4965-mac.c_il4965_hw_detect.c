#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct il_priv {int /*<<< orphan*/  rev_id; TYPE_1__* pci_dev; void* hw_wa_rev; void* hw_rev; } ;
struct TYPE_2__ {int /*<<< orphan*/  revision; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_HW_REV ; 
 int /*<<< orphan*/  CSR_HW_REV_WA_REG ; 
 int /*<<< orphan*/  D_INFO (char*,int /*<<< orphan*/ ) ; 
 void* _il_rd (struct il_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
il4965_hw_detect(struct il_priv *il)
{
	il->hw_rev = _il_rd(il, CSR_HW_REV);
	il->hw_wa_rev = _il_rd(il, CSR_HW_REV_WA_REG);
	il->rev_id = il->pci_dev->revision;
	D_INFO("HW Revision ID = 0x%X\n", il->rev_id);
}