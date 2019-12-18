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
typedef  int u8 ;
typedef  int u16 ;
struct TYPE_2__ {int /*<<< orphan*/  phy_rev; } ;
struct brcms_phy {TYPE_1__ pubpi; } ;

/* Variables and functions */
 scalar_t__ NREV_GE (int /*<<< orphan*/ ,int) ; 
 scalar_t__ NREV_LT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  and_phy_reg (struct brcms_phy*,int,int) ; 
 int /*<<< orphan*/  mod_phy_reg (struct brcms_phy*,int,int,int) ; 
 int /*<<< orphan*/  or_phy_reg (struct brcms_phy*,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void
wlc_phy_rfctrl_override_nphy(struct brcms_phy *pi, u16 field, u16 value,
			     u8 core_mask, u8 off)
{
	u8 core_num;
	u16 addr = 0, mask = 0, en_addr = 0, val_addr = 0, en_mask =
		0, val_mask = 0;
	u8 shift = 0, val_shift = 0;

	if (NREV_GE(pi->pubpi.phy_rev, 3) && NREV_LT(pi->pubpi.phy_rev, 7)) {

		en_mask = field;
		for (core_num = 0; core_num < 2; core_num++) {

			switch (field) {
			case (0x1 << 1):
				en_addr = (core_num == 0) ? 0xe7 : 0xec;
				val_addr = (core_num == 0) ? 0x7a : 0x7d;
				val_mask = (0x1 << 0);
				val_shift = 0;
				break;
			case (0x1 << 2):
				en_addr = (core_num == 0) ? 0xe7 : 0xec;
				val_addr = (core_num == 0) ? 0x7a : 0x7d;
				val_mask = (0x1 << 1);
				val_shift = 1;
				break;
			case (0x1 << 3):
				en_addr = (core_num == 0) ? 0xe7 : 0xec;
				val_addr = (core_num == 0) ? 0x7a : 0x7d;
				val_mask = (0x1 << 2);
				val_shift = 2;
				break;
			case (0x1 << 4):
				en_addr = (core_num == 0) ? 0xe7 : 0xec;
				val_addr = (core_num == 0) ? 0x7a : 0x7d;
				val_mask = (0x1 << 4);
				val_shift = 4;
				break;
			case (0x1 << 5):
				en_addr = (core_num == 0) ? 0xe7 : 0xec;
				val_addr = (core_num == 0) ? 0x7a : 0x7d;
				val_mask = (0x1 << 5);
				val_shift = 5;
				break;
			case (0x1 << 6):
				en_addr = (core_num == 0) ? 0xe7 : 0xec;
				val_addr = (core_num == 0) ? 0x7a : 0x7d;
				val_mask = (0x1 << 6);
				val_shift = 6;
				break;
			case (0x1 << 7):
				en_addr = (core_num == 0) ? 0xe7 : 0xec;
				val_addr = (core_num == 0) ? 0x7a : 0x7d;
				val_mask = (0x1 << 7);
				val_shift = 7;
				break;
			case (0x1 << 8):
				en_addr = (core_num == 0) ? 0xe7 : 0xec;
				val_addr = (core_num == 0) ? 0x7a : 0x7d;
				val_mask = (0x7 << 8);
				val_shift = 8;
				break;
			case (0x1 << 11):
				en_addr = (core_num == 0) ? 0xe7 : 0xec;
				val_addr = (core_num == 0) ? 0x7a : 0x7d;
				val_mask = (0x7 << 13);
				val_shift = 13;
				break;

			case (0x1 << 9):
				en_addr = (core_num == 0) ? 0xe7 : 0xec;
				val_addr = (core_num == 0) ? 0xf8 : 0xfa;
				val_mask = (0x7 << 0);
				val_shift = 0;
				break;

			case (0x1 << 10):
				en_addr = (core_num == 0) ? 0xe7 : 0xec;
				val_addr = (core_num == 0) ? 0xf8 : 0xfa;
				val_mask = (0x7 << 4);
				val_shift = 4;
				break;

			case (0x1 << 12):
				en_addr = (core_num == 0) ? 0xe7 : 0xec;
				val_addr = (core_num == 0) ? 0x7b : 0x7e;
				val_mask = (0xffff << 0);
				val_shift = 0;
				break;
			case (0x1 << 13):
				en_addr = (core_num == 0) ? 0xe7 : 0xec;
				val_addr = (core_num == 0) ? 0x7c : 0x7f;
				val_mask = (0xffff << 0);
				val_shift = 0;
				break;
			case (0x1 << 14):
				en_addr = (core_num == 0) ? 0xe7 : 0xec;
				val_addr = (core_num == 0) ? 0xf9 : 0xfb;
				val_mask = (0x3 << 6);
				val_shift = 6;
				break;
			case (0x1 << 0):
				en_addr = (core_num == 0) ? 0xe5 : 0xe6;
				val_addr = (core_num == 0) ? 0xf9 : 0xfb;
				val_mask = (0x1 << 15);
				val_shift = 15;
				break;
			default:
				addr = 0xffff;
				break;
			}

			if (off) {
				and_phy_reg(pi, en_addr, ~en_mask);
				and_phy_reg(pi, val_addr, ~val_mask);
			} else {

				if ((core_mask == 0)
				    || (core_mask & (1 << core_num))) {
					or_phy_reg(pi, en_addr, en_mask);

					if (addr != 0xffff)
						mod_phy_reg(pi, val_addr,
							    val_mask,
							    (value <<
							     val_shift));
				}
			}
		}
	} else {

		if (off) {
			and_phy_reg(pi, 0xec, ~field);
			value = 0x0;
		} else {
			or_phy_reg(pi, 0xec, field);
		}

		for (core_num = 0; core_num < 2; core_num++) {

			switch (field) {
			case (0x1 << 1):
			case (0x1 << 9):
			case (0x1 << 12):
			case (0x1 << 13):
			case (0x1 << 14):
				addr = 0x78;

				core_mask = 0x1;
				break;
			case (0x1 << 2):
			case (0x1 << 3):
			case (0x1 << 4):
			case (0x1 << 5):
			case (0x1 << 6):
			case (0x1 << 7):
			case (0x1 << 8):
				addr = (core_num == 0) ? 0x7a : 0x7d;
				break;
			case (0x1 << 10):
				addr = (core_num == 0) ? 0x7b : 0x7e;
				break;
			case (0x1 << 11):
				addr = (core_num == 0) ? 0x7c : 0x7f;
				break;
			default:
				addr = 0xffff;
			}

			switch (field) {
			case (0x1 << 1):
				mask = (0x7 << 3);
				shift = 3;
				break;
			case (0x1 << 9):
				mask = (0x1 << 2);
				shift = 2;
				break;
			case (0x1 << 12):
				mask = (0x1 << 8);
				shift = 8;
				break;
			case (0x1 << 13):
				mask = (0x1 << 9);
				shift = 9;
				break;
			case (0x1 << 14):
				mask = (0xf << 12);
				shift = 12;
				break;
			case (0x1 << 2):
				mask = (0x1 << 0);
				shift = 0;
				break;
			case (0x1 << 3):
				mask = (0x1 << 1);
				shift = 1;
				break;
			case (0x1 << 4):
				mask = (0x1 << 2);
				shift = 2;
				break;
			case (0x1 << 5):
				mask = (0x3 << 4);
				shift = 4;
				break;
			case (0x1 << 6):
				mask = (0x3 << 6);
				shift = 6;
				break;
			case (0x1 << 7):
				mask = (0x1 << 8);
				shift = 8;
				break;
			case (0x1 << 8):
				mask = (0x1 << 9);
				shift = 9;
				break;
			case (0x1 << 10):
				mask = 0x1fff;
				shift = 0x0;
				break;
			case (0x1 << 11):
				mask = 0x1fff;
				shift = 0x0;
				break;
			default:
				mask = 0x0;
				shift = 0x0;
				break;
			}

			if ((addr != 0xffff) && (core_mask & (1 << core_num)))
				mod_phy_reg(pi, addr, mask, (value << shift));
		}

		or_phy_reg(pi, 0xec, (0x1 << 0));
		or_phy_reg(pi, 0x78, (0x1 << 0));
		udelay(1);
		and_phy_reg(pi, 0xec, ~(0x1 << 0));
	}
}