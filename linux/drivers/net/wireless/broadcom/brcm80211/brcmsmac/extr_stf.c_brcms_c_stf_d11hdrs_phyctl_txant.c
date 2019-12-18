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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct brcms_c_info {int /*<<< orphan*/  band; TYPE_1__* stf; } ;
struct TYPE_2__ {int phytxant; } ;

/* Variables and functions */
 scalar_t__ BRCMS_ISNPHY (int /*<<< orphan*/ ) ; 
 int PHY_TXC_ANT_MASK ; 
 int PHY_TXC_HTANT_MASK ; 
 int _brcms_c_stf_phytxchain_sel (struct brcms_c_info*,int /*<<< orphan*/ ) ; 

u16 brcms_c_stf_d11hdrs_phyctl_txant(struct brcms_c_info *wlc, u32 rspec)
{
	u16 phytxant = wlc->stf->phytxant;
	u16 mask = PHY_TXC_ANT_MASK;

	/* for non-siso rates or default setting, use the available chains */
	if (BRCMS_ISNPHY(wlc->band)) {
		phytxant = _brcms_c_stf_phytxchain_sel(wlc, rspec);
		mask = PHY_TXC_HTANT_MASK;
	}
	phytxant |= phytxant & mask;
	return phytxant;
}