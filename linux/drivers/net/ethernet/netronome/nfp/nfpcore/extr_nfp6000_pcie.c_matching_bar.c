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
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct nfp_bar {scalar_t__ base; int bitsize; int /*<<< orphan*/  barcfg; } ;

/* Variables and functions */
 int NFP_CPP_ACTION_RW ; 
 int NFP_PCIE_BAR_PCIE2CPP_Action_BaseAddress_of (int /*<<< orphan*/ ) ; 
#define  NFP_PCIE_BAR_PCIE2CPP_LengthSelect_0BYTE 133 
#define  NFP_PCIE_BAR_PCIE2CPP_LengthSelect_32BIT 132 
#define  NFP_PCIE_BAR_PCIE2CPP_LengthSelect_64BIT 131 
 int NFP_PCIE_BAR_PCIE2CPP_LengthSelect_of (int /*<<< orphan*/ ) ; 
#define  NFP_PCIE_BAR_PCIE2CPP_MapType_BULK 130 
#define  NFP_PCIE_BAR_PCIE2CPP_MapType_FIXED 129 
#define  NFP_PCIE_BAR_PCIE2CPP_MapType_TARGET 128 
 int NFP_PCIE_BAR_PCIE2CPP_MapType_of (int /*<<< orphan*/ ) ; 
 int NFP_PCIE_BAR_PCIE2CPP_Target_BaseAddress_of (int /*<<< orphan*/ ) ; 
 int NFP_PCIE_BAR_PCIE2CPP_Token_BaseAddress_of (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int matching_bar(struct nfp_bar *bar, u32 tgt, u32 act, u32 tok,
			u64 offset, size_t size, int width)
{
	int bartgt, baract, bartok;
	int barwidth;
	u32 maptype;

	maptype = NFP_PCIE_BAR_PCIE2CPP_MapType_of(bar->barcfg);
	bartgt = NFP_PCIE_BAR_PCIE2CPP_Target_BaseAddress_of(bar->barcfg);
	bartok = NFP_PCIE_BAR_PCIE2CPP_Token_BaseAddress_of(bar->barcfg);
	baract = NFP_PCIE_BAR_PCIE2CPP_Action_BaseAddress_of(bar->barcfg);

	barwidth = NFP_PCIE_BAR_PCIE2CPP_LengthSelect_of(bar->barcfg);
	switch (barwidth) {
	case NFP_PCIE_BAR_PCIE2CPP_LengthSelect_32BIT:
		barwidth = 4;
		break;
	case NFP_PCIE_BAR_PCIE2CPP_LengthSelect_64BIT:
		barwidth = 8;
		break;
	case NFP_PCIE_BAR_PCIE2CPP_LengthSelect_0BYTE:
		barwidth = 0;
		break;
	default:
		barwidth = -1;
		break;
	}

	switch (maptype) {
	case NFP_PCIE_BAR_PCIE2CPP_MapType_TARGET:
		bartok = -1;
		/* FALLTHROUGH */
	case NFP_PCIE_BAR_PCIE2CPP_MapType_BULK:
		baract = NFP_CPP_ACTION_RW;
		if (act == 0)
			act = NFP_CPP_ACTION_RW;
		/* FALLTHROUGH */
	case NFP_PCIE_BAR_PCIE2CPP_MapType_FIXED:
		break;
	default:
		/* We don't match explicit bars through the area interface */
		return 0;
	}

	/* Make sure to match up the width */
	if (barwidth != width)
		return 0;

	if ((bartgt < 0 || bartgt == tgt) &&
	    (bartok < 0 || bartok == tok) &&
	    (baract == act) &&
	    bar->base <= offset &&
	    (bar->base + (1 << bar->bitsize)) >= (offset + size))
		return 1;

	/* No match */
	return 0;
}