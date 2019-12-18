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
struct b43_phy {int rev; } ;
struct b43_wldev {struct b43_phy phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_OFDMTAB_AGC2 ; 
 int B43_TAB_NOISEG1_SIZE ; 
 int B43_TAB_NOISEG2_SIZE ; 
 int /*<<< orphan*/  b43_ofdmtab_write16 (struct b43_wldev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * b43_tab_noiseg1 ; 
 int /*<<< orphan*/ * b43_tab_noiseg2 ; 

__attribute__((used)) static void b43_wa_nft(struct b43_wldev *dev) /* Noise figure table */
{
	struct b43_phy *phy = &dev->phy;
	int i;

	if (phy->rev == 1)
		for (i = 0; i < B43_TAB_NOISEG1_SIZE; i++)
			b43_ofdmtab_write16(dev, B43_OFDMTAB_AGC2, i,
					    b43_tab_noiseg1[i]);
	else
		for (i = 0; i < B43_TAB_NOISEG2_SIZE; i++)
			b43_ofdmtab_write16(dev, B43_OFDMTAB_AGC2, i,
					    b43_tab_noiseg2[i]);
}