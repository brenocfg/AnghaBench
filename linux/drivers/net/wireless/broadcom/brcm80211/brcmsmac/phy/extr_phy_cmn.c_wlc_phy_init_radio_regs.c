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
typedef  size_t uint ;
typedef  int u16 ;
struct radio_regs {int address; scalar_t__ init_g; scalar_t__ do_init_g; scalar_t__ init_a; scalar_t__ do_init_a; } ;
struct brcms_phy {int /*<<< orphan*/  radio_chanspec; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMS_PHY_WAR_PR51571 (struct brcms_phy*) ; 
 scalar_t__ CHSPEC_IS5G (int /*<<< orphan*/ ) ; 
 scalar_t__ ISNPHY (struct brcms_phy*) ; 
 int /*<<< orphan*/  write_radio_reg (struct brcms_phy*,int,int) ; 

uint
wlc_phy_init_radio_regs(struct brcms_phy *pi,
			const struct radio_regs *radioregs,
			u16 core_offset)
{
	uint i = 0;
	uint count = 0;

	do {
		if (CHSPEC_IS5G(pi->radio_chanspec)) {
			if (radioregs[i].do_init_a) {
				write_radio_reg(pi,
						radioregs[i].
						address | core_offset,
						(u16) radioregs[i].init_a);
				if (ISNPHY(pi) && (++count % 4 == 0))
					BRCMS_PHY_WAR_PR51571(pi);
			}
		} else {
			if (radioregs[i].do_init_g) {
				write_radio_reg(pi,
						radioregs[i].
						address | core_offset,
						(u16) radioregs[i].init_g);
				if (ISNPHY(pi) && (++count % 4 == 0))
					BRCMS_PHY_WAR_PR51571(pi);
			}
		}

		i++;
	} while (radioregs[i].address != 0xffff);

	return i;
}