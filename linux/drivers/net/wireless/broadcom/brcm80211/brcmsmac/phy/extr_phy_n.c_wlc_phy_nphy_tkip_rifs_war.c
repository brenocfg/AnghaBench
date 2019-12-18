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
typedef  scalar_t__ u8 ;
typedef  int u16 ;
struct brcms_phy {TYPE_1__* sh; } ;
struct TYPE_2__ {scalar_t__ _rifs_phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  wlc_phy_write_txmacreg_nphy (struct brcms_phy*,int,int) ; 

void wlc_phy_nphy_tkip_rifs_war(struct brcms_phy *pi, u8 rifs)
{
	u16 holdoff, delay;

	if (rifs) {

		holdoff = 0x10;
		delay = 0x258;
	} else {

		holdoff = 0x15;
		delay = 0x320;
	}

	wlc_phy_write_txmacreg_nphy(pi, holdoff, delay);

	if (pi->sh && (pi->sh->_rifs_phy != rifs))
		pi->sh->_rifs_phy = rifs;
}