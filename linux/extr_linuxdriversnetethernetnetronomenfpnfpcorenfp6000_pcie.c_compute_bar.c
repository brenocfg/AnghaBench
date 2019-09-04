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
typedef  size_t u64 ;
typedef  size_t u32 ;
struct nfp_bar {int bitsize; } ;
struct nfp6000_pcie {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int NFP_CPP_ACTION_RW ; 
 int NFP_CPP_NUM_TARGETS ; 
 size_t NFP_PCIE_BAR_PCIE2CPP_Action_BaseAddress (int) ; 
 size_t NFP_PCIE_BAR_PCIE2CPP_LengthSelect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFP_PCIE_BAR_PCIE2CPP_LengthSelect_0BYTE ; 
 int /*<<< orphan*/  NFP_PCIE_BAR_PCIE2CPP_LengthSelect_32BIT ; 
 int /*<<< orphan*/  NFP_PCIE_BAR_PCIE2CPP_LengthSelect_64BIT ; 
 size_t NFP_PCIE_BAR_PCIE2CPP_MapType (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFP_PCIE_BAR_PCIE2CPP_MapType_BULK ; 
 int /*<<< orphan*/  NFP_PCIE_BAR_PCIE2CPP_MapType_FIXED ; 
 size_t NFP_PCIE_BAR_PCIE2CPP_Target_BaseAddress (int) ; 
 size_t NFP_PCIE_BAR_PCIE2CPP_Token_BaseAddress (int) ; 
 int NFP_PCIE_P2C_BULK_SIZE (struct nfp_bar const*) ; 
 int NFP_PCIE_P2C_FIXED_SIZE (struct nfp_bar const*) ; 

__attribute__((used)) static int
compute_bar(const struct nfp6000_pcie *nfp, const struct nfp_bar *bar,
	    u32 *bar_config, u64 *bar_base,
	    int tgt, int act, int tok, u64 offset, size_t size, int width)
{
	int bitsize;
	u32 newcfg;

	if (tgt >= NFP_CPP_NUM_TARGETS)
		return -EINVAL;

	switch (width) {
	case 8:
		newcfg = NFP_PCIE_BAR_PCIE2CPP_LengthSelect(
			NFP_PCIE_BAR_PCIE2CPP_LengthSelect_64BIT);
		break;
	case 4:
		newcfg = NFP_PCIE_BAR_PCIE2CPP_LengthSelect(
			NFP_PCIE_BAR_PCIE2CPP_LengthSelect_32BIT);
		break;
	case 0:
		newcfg = NFP_PCIE_BAR_PCIE2CPP_LengthSelect(
			NFP_PCIE_BAR_PCIE2CPP_LengthSelect_0BYTE);
		break;
	default:
		return -EINVAL;
	}

	if (act != NFP_CPP_ACTION_RW && act != 0) {
		/* Fixed CPP mapping with specific action */
		u64 mask = ~(NFP_PCIE_P2C_FIXED_SIZE(bar) - 1);

		newcfg |= NFP_PCIE_BAR_PCIE2CPP_MapType(
			  NFP_PCIE_BAR_PCIE2CPP_MapType_FIXED);
		newcfg |= NFP_PCIE_BAR_PCIE2CPP_Target_BaseAddress(tgt);
		newcfg |= NFP_PCIE_BAR_PCIE2CPP_Action_BaseAddress(act);
		newcfg |= NFP_PCIE_BAR_PCIE2CPP_Token_BaseAddress(tok);

		if ((offset & mask) != ((offset + size - 1) & mask))
			return -EINVAL;
		offset &= mask;

		bitsize = 40 - 16;
	} else {
		u64 mask = ~(NFP_PCIE_P2C_BULK_SIZE(bar) - 1);

		/* Bulk mapping */
		newcfg |= NFP_PCIE_BAR_PCIE2CPP_MapType(
			NFP_PCIE_BAR_PCIE2CPP_MapType_BULK);
		newcfg |= NFP_PCIE_BAR_PCIE2CPP_Target_BaseAddress(tgt);
		newcfg |= NFP_PCIE_BAR_PCIE2CPP_Token_BaseAddress(tok);

		if ((offset & mask) != ((offset + size - 1) & mask))
			return -EINVAL;

		offset &= mask;

		bitsize = 40 - 21;
	}

	if (bar->bitsize < bitsize)
		return -EINVAL;

	newcfg |= offset >> bitsize;

	if (bar_base)
		*bar_base = offset;

	if (bar_config)
		*bar_config = newcfg;

	return 0;
}