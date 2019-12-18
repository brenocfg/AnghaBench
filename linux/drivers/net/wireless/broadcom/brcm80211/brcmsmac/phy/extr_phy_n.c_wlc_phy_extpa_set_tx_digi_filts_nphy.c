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
typedef  int u16 ;
struct brcms_phy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ ** NPHY_IPA_REV4_txdigi_filtcoeffs ; 
 int NPHY_NUM_DIG_FILT_COEFFS ; 
 int /*<<< orphan*/  write_phy_reg (struct brcms_phy*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wlc_phy_extpa_set_tx_digi_filts_nphy(struct brcms_phy *pi)
{
	int j, type = 2;
	u16 addr_offset = 0x2c5;

	for (j = 0; j < NPHY_NUM_DIG_FILT_COEFFS; j++)
		write_phy_reg(pi, addr_offset + j,
			      NPHY_IPA_REV4_txdigi_filtcoeffs[type][j]);
}