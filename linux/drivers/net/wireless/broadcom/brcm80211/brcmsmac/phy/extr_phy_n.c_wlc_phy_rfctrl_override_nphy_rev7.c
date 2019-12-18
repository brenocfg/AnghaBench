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
 int NPHY_REV7_RFCTRLOVERRIDE_ID0 ; 
 int NPHY_REV7_RFCTRLOVERRIDE_ID1 ; 
 int NPHY_REV7_RFCTRLOVERRIDE_ID2 ; 
 scalar_t__ NREV_GE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  and_phy_reg (struct brcms_phy*,int,int) ; 
 int /*<<< orphan*/  mod_phy_reg (struct brcms_phy*,int,int,int) ; 
 int /*<<< orphan*/  or_phy_reg (struct brcms_phy*,int,int) ; 

__attribute__((used)) static void
wlc_phy_rfctrl_override_nphy_rev7(struct brcms_phy *pi, u16 field, u16 value,
				  u8 core_mask, u8 off, u8 override_id)
{
	u8 core_num;
	u16 addr = 0, en_addr = 0, val_addr = 0, en_mask = 0, val_mask = 0;
	u8 val_shift = 0;

	if (NREV_GE(pi->pubpi.phy_rev, 7)) {
		en_mask = field;
		for (core_num = 0; core_num < 2; core_num++) {
			if (override_id == NPHY_REV7_RFCTRLOVERRIDE_ID0) {

				switch (field) {
				case (0x1 << 2):
					en_addr = (core_num == 0) ? 0xe7 : 0xec;
					val_addr = (core_num == 0) ? 0x7a :
						   0x7d;
					val_mask = (0x1 << 1);
					val_shift = 1;
					break;
				case (0x1 << 3):
					en_addr = (core_num == 0) ? 0xe7 : 0xec;
					val_addr = (core_num == 0) ? 0x7a :
						   0x7d;
					val_mask = (0x1 << 2);
					val_shift = 2;
					break;
				case (0x1 << 4):
					en_addr = (core_num == 0) ? 0xe7 : 0xec;
					val_addr = (core_num == 0) ? 0x7a :
						   0x7d;
					val_mask = (0x1 << 4);
					val_shift = 4;
					break;
				case (0x1 << 5):
					en_addr = (core_num == 0) ? 0xe7 : 0xec;
					val_addr = (core_num == 0) ? 0x7a :
						   0x7d;
					val_mask = (0x1 << 5);
					val_shift = 5;
					break;
				case (0x1 << 6):
					en_addr = (core_num == 0) ? 0xe7 : 0xec;
					val_addr = (core_num == 0) ? 0x7a :
						   0x7d;
					val_mask = (0x1 << 6);
					val_shift = 6;
					break;
				case (0x1 << 7):
					en_addr = (core_num == 0) ? 0xe7 : 0xec;
					val_addr = (core_num == 0) ? 0x7a :
						   0x7d;
					val_mask = (0x1 << 7);
					val_shift = 7;
					break;
				case (0x1 << 10):
					en_addr = (core_num == 0) ? 0xe7 : 0xec;
					val_addr = (core_num == 0) ? 0xf8 :
						   0xfa;
					val_mask = (0x7 << 4);
					val_shift = 4;
					break;
				case (0x1 << 11):
					en_addr = (core_num == 0) ? 0xe7 : 0xec;
					val_addr = (core_num == 0) ? 0x7b :
						   0x7e;
					val_mask = (0xffff << 0);
					val_shift = 0;
					break;
				case (0x1 << 12):
					en_addr = (core_num == 0) ? 0xe7 : 0xec;
					val_addr = (core_num == 0) ? 0x7c :
						   0x7f;
					val_mask = (0xffff << 0);
					val_shift = 0;
					break;
				case (0x3 << 13):
					en_addr = (core_num == 0) ? 0xe7 : 0xec;
					val_addr = (core_num == 0) ? 0x348 :
						   0x349;
					val_mask = (0xff << 0);
					val_shift = 0;
					break;
				case (0x1 << 13):
					en_addr = (core_num == 0) ? 0xe7 : 0xec;
					val_addr = (core_num == 0) ? 0x348 :
						   0x349;
					val_mask = (0xf << 0);
					val_shift = 0;
					break;
				default:
					addr = 0xffff;
					break;
				}
			} else if (override_id ==
				   NPHY_REV7_RFCTRLOVERRIDE_ID1) {

				switch (field) {
				case (0x1 << 1):
					en_addr = (core_num == 0) ? 0x342 :
						  0x343;
					val_addr = (core_num == 0) ? 0x340 :
						   0x341;
					val_mask = (0x1 << 1);
					val_shift = 1;
					break;
				case (0x1 << 3):
					en_addr = (core_num == 0) ? 0x342 :
						  0x343;
					val_addr = (core_num == 0) ? 0x340 :
						   0x341;
					val_mask = (0x1 << 3);
					val_shift = 3;
					break;
				case (0x1 << 5):
					en_addr = (core_num == 0) ? 0x342 :
						  0x343;
					val_addr = (core_num == 0) ? 0x340 :
						   0x341;
					val_mask = (0x1 << 5);
					val_shift = 5;
					break;
				case (0x1 << 4):
					en_addr = (core_num == 0) ? 0x342 :
						  0x343;
					val_addr = (core_num == 0) ? 0x340 :
						   0x341;
					val_mask = (0x1 << 4);
					val_shift = 4;
					break;
				case (0x1 << 2):

					en_addr = (core_num == 0) ? 0x342 :
						  0x343;
					val_addr = (core_num == 0) ? 0x340 :
						   0x341;
					val_mask = (0x1 << 2);
					val_shift = 2;
					break;
				case (0x1 << 7):

					en_addr = (core_num == 0) ? 0x342 :
						  0x343;
					val_addr = (core_num == 0) ? 0x340 :
						   0x341;
					val_mask = (0x7 << 8);
					val_shift = 8;
					break;
				case (0x1 << 11):
					en_addr = (core_num == 0) ? 0x342 :
						  0x343;
					val_addr = (core_num == 0) ? 0x340 :
						   0x341;
					val_mask = (0x1 << 14);
					val_shift = 14;
					break;
				case (0x1 << 10):
					en_addr = (core_num == 0) ? 0x342 :
						  0x343;
					val_addr = (core_num == 0) ? 0x340 :
						   0x341;
					val_mask = (0x1 << 13);
					val_shift = 13;
					break;
				case (0x1 << 9):
					en_addr = (core_num == 0) ? 0x342 :
						  0x343;
					val_addr = (core_num == 0) ? 0x340 :
						   0x341;
					val_mask = (0x1 << 12);
					val_shift = 12;
					break;
				case (0x1 << 8):
					en_addr = (core_num == 0) ? 0x342 :
						  0x343;
					val_addr = (core_num == 0) ? 0x340 :
						   0x341;
					val_mask = (0x1 << 11);
					val_shift = 11;
					break;
				case (0x1 << 6):
					en_addr = (core_num == 0) ? 0x342 :
						  0x343;
					val_addr = (core_num == 0) ? 0x340 :
						   0x341;
					val_mask = (0x1 << 6);
					val_shift = 6;
					break;
				case (0x1 << 0):
					en_addr = (core_num == 0) ? 0x342 :
						  0x343;
					val_addr = (core_num == 0) ? 0x340 :
						   0x341;
					val_mask = (0x1 << 0);
					val_shift = 0;
					break;
				default:
					addr = 0xffff;
					break;
				}
			} else if (override_id ==
				   NPHY_REV7_RFCTRLOVERRIDE_ID2) {

				switch (field) {
				case (0x1 << 3):
					en_addr = (core_num == 0) ? 0x346 :
						  0x347;
					val_addr = (core_num == 0) ? 0x344 :
						   0x345;
					val_mask = (0x1 << 3);
					val_shift = 3;
					break;
				case (0x1 << 1):
					en_addr = (core_num == 0) ? 0x346 :
						  0x347;
					val_addr = (core_num == 0) ? 0x344 :
						   0x345;
					val_mask = (0x1 << 1);
					val_shift = 1;
					break;
				case (0x1 << 0):
					en_addr = (core_num == 0) ? 0x346 :
						  0x347;
					val_addr = (core_num == 0) ? 0x344 :
						   0x345;
					val_mask = (0x1 << 0);
					val_shift = 0;
					break;
				case (0x1 << 2):
					en_addr = (core_num == 0) ? 0x346 :
						  0x347;
					val_addr = (core_num == 0) ? 0x344 :
						   0x345;
					val_mask = (0x1 << 2);
					val_shift = 2;
					break;
				case (0x1 << 4):
					en_addr = (core_num == 0) ? 0x346 :
						  0x347;
					val_addr = (core_num == 0) ? 0x344 :
						   0x345;
					val_mask = (0x1 << 4);
					val_shift = 4;
					break;
				default:
					addr = 0xffff;
					break;
				}
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
	}
}