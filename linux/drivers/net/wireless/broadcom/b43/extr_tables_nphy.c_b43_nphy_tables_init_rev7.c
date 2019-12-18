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
struct TYPE_2__ {scalar_t__ do_full_init; } ;
struct b43_wldev {TYPE_1__ phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_NTAB_CHANEST_R3 ; 
 int /*<<< orphan*/  B43_NTAB_FRAMELT_R3 ; 
 int /*<<< orphan*/  B43_NTAB_FRAMESTRUCT_R3 ; 
 int /*<<< orphan*/  B43_NTAB_INTLEVEL_R3 ; 
 int /*<<< orphan*/  B43_NTAB_MCS_R3 ; 
 int /*<<< orphan*/  B43_NTAB_NOISEVAR_R7 ; 
 int /*<<< orphan*/  B43_NTAB_PILOTLT_R3 ; 
 int /*<<< orphan*/  B43_NTAB_PILOT_R3 ; 
 int /*<<< orphan*/  B43_NTAB_TDI20A0_R3 ; 
 int /*<<< orphan*/  B43_NTAB_TDI20A1_R3 ; 
 int /*<<< orphan*/  B43_NTAB_TDI40A0_R3 ; 
 int /*<<< orphan*/  B43_NTAB_TDI40A1_R3 ; 
 int /*<<< orphan*/  B43_NTAB_TDTRN_R3 ; 
 int /*<<< orphan*/  B43_NTAB_TMAP_R7 ; 
 int /*<<< orphan*/  b43_nphy_tables_init_rev7_volatile (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_nphy_tables_init_shared_lut (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_ntab_channelest_r3 ; 
 int /*<<< orphan*/  b43_ntab_framelookup_r3 ; 
 int /*<<< orphan*/  b43_ntab_framestruct_r3 ; 
 int /*<<< orphan*/  b43_ntab_intlevel_r3 ; 
 int /*<<< orphan*/  b43_ntab_mcs_r3 ; 
 int /*<<< orphan*/  b43_ntab_noisevar_r7 ; 
 int /*<<< orphan*/  b43_ntab_pilot_r3 ; 
 int /*<<< orphan*/  b43_ntab_pilotlt_r3 ; 
 int /*<<< orphan*/  b43_ntab_tdi20a0_r3 ; 
 int /*<<< orphan*/  b43_ntab_tdi20a1_r3 ; 
 int /*<<< orphan*/  b43_ntab_tdi40a0_r3 ; 
 int /*<<< orphan*/  b43_ntab_tdi40a1_r3 ; 
 int /*<<< orphan*/  b43_ntab_tdtrn_r3 ; 
 int /*<<< orphan*/  b43_ntab_tmap_r7 ; 
 int /*<<< orphan*/  ntab_upload (struct b43_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void b43_nphy_tables_init_rev7(struct b43_wldev *dev)
{
	/* Static tables */
	if (dev->phy.do_full_init) {
		ntab_upload(dev, B43_NTAB_FRAMESTRUCT_R3, b43_ntab_framestruct_r3);
		ntab_upload(dev, B43_NTAB_PILOT_R3, b43_ntab_pilot_r3);
		ntab_upload(dev, B43_NTAB_TMAP_R7, b43_ntab_tmap_r7);
		ntab_upload(dev, B43_NTAB_INTLEVEL_R3, b43_ntab_intlevel_r3);
		ntab_upload(dev, B43_NTAB_TDTRN_R3, b43_ntab_tdtrn_r3);
		ntab_upload(dev, B43_NTAB_NOISEVAR_R7, b43_ntab_noisevar_r7);
		ntab_upload(dev, B43_NTAB_MCS_R3, b43_ntab_mcs_r3);
		ntab_upload(dev, B43_NTAB_TDI20A0_R3, b43_ntab_tdi20a0_r3);
		ntab_upload(dev, B43_NTAB_TDI20A1_R3, b43_ntab_tdi20a1_r3);
		ntab_upload(dev, B43_NTAB_TDI40A0_R3, b43_ntab_tdi40a0_r3);
		ntab_upload(dev, B43_NTAB_TDI40A1_R3, b43_ntab_tdi40a1_r3);
		ntab_upload(dev, B43_NTAB_PILOTLT_R3, b43_ntab_pilotlt_r3);
		ntab_upload(dev, B43_NTAB_CHANEST_R3, b43_ntab_channelest_r3);
		ntab_upload(dev, B43_NTAB_FRAMELT_R3, b43_ntab_framelookup_r3);
		b43_nphy_tables_init_shared_lut(dev);
	}

	/* Volatile tables */
	b43_nphy_tables_init_rev7_volatile(dev);
}