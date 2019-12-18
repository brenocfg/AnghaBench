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
typedef  int u8 ;
typedef  int u32 ;
struct brcmf_core_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOCRAMREGOFFS (int) ; 
 int SOCRAM_BANKIDX_MEMTYPE_SHIFT ; 
 int SOCRAM_BANKINFO_RETNTRAM_MASK ; 
 int SOCRAM_BANKINFO_SZBASE ; 
 int SOCRAM_BANKINFO_SZMASK ; 
 int SOCRAM_MEMTYPE_RAM ; 
 int brcmf_chip_core_read32 (struct brcmf_core_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_chip_core_write32 (struct brcmf_core_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool brcmf_chip_socram_banksize(struct brcmf_core_priv *core, u8 idx,
				       u32 *banksize)
{
	u32 bankinfo;
	u32 bankidx = (SOCRAM_MEMTYPE_RAM << SOCRAM_BANKIDX_MEMTYPE_SHIFT);

	bankidx |= idx;
	brcmf_chip_core_write32(core, SOCRAMREGOFFS(bankidx), bankidx);
	bankinfo = brcmf_chip_core_read32(core, SOCRAMREGOFFS(bankinfo));
	*banksize = (bankinfo & SOCRAM_BANKINFO_SZMASK) + 1;
	*banksize *= SOCRAM_BANKINFO_SZBASE;
	return !!(bankinfo & SOCRAM_BANKINFO_RETNTRAM_MASK);
}