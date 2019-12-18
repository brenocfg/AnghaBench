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
typedef  int /*<<< orphan*/  u16 ;
struct radio_regs {int dummy; } ;
struct TYPE_2__ {int radiorev; int /*<<< orphan*/  phy_rev; } ;
struct brcms_phy {TYPE_1__ pubpi; } ;

/* Variables and functions */
 scalar_t__ NREV_IS (int /*<<< orphan*/ ,int) ; 
 scalar_t__ RADIO_2056_RX0 ; 
 scalar_t__ RADIO_2056_RX1 ; 
 scalar_t__ RADIO_2056_SYN ; 
 scalar_t__ RADIO_2056_TX0 ; 
 scalar_t__ RADIO_2056_TX1 ; 
 struct radio_regs* regs_RX_2056 ; 
 struct radio_regs* regs_RX_2056_A1 ; 
 struct radio_regs* regs_RX_2056_rev11 ; 
 struct radio_regs* regs_RX_2056_rev5 ; 
 struct radio_regs* regs_RX_2056_rev6 ; 
 struct radio_regs* regs_RX_2056_rev7 ; 
 struct radio_regs* regs_RX_2056_rev8 ; 
 struct radio_regs* regs_SYN_2056 ; 
 struct radio_regs* regs_SYN_2056_A1 ; 
 struct radio_regs* regs_SYN_2056_rev11 ; 
 struct radio_regs* regs_SYN_2056_rev5 ; 
 struct radio_regs* regs_SYN_2056_rev6 ; 
 struct radio_regs* regs_SYN_2056_rev7 ; 
 struct radio_regs* regs_SYN_2056_rev8 ; 
 struct radio_regs* regs_TX_2056 ; 
 struct radio_regs* regs_TX_2056_A1 ; 
 struct radio_regs* regs_TX_2056_rev11 ; 
 struct radio_regs* regs_TX_2056_rev5 ; 
 struct radio_regs* regs_TX_2056_rev6 ; 
 struct radio_regs* regs_TX_2056_rev7 ; 
 struct radio_regs* regs_TX_2056_rev8 ; 
 int /*<<< orphan*/  wlc_phy_init_radio_regs (struct brcms_phy*,struct radio_regs const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wlc_phy_radio_init_2056(struct brcms_phy *pi)
{
	const struct radio_regs *regs_SYN_2056_ptr = NULL;
	const struct radio_regs *regs_TX_2056_ptr = NULL;
	const struct radio_regs *regs_RX_2056_ptr = NULL;

	if (NREV_IS(pi->pubpi.phy_rev, 3)) {
		regs_SYN_2056_ptr = regs_SYN_2056;
		regs_TX_2056_ptr = regs_TX_2056;
		regs_RX_2056_ptr = regs_RX_2056;
	} else if (NREV_IS(pi->pubpi.phy_rev, 4)) {
		regs_SYN_2056_ptr = regs_SYN_2056_A1;
		regs_TX_2056_ptr = regs_TX_2056_A1;
		regs_RX_2056_ptr = regs_RX_2056_A1;
	} else {
		switch (pi->pubpi.radiorev) {
		case 5:
			regs_SYN_2056_ptr = regs_SYN_2056_rev5;
			regs_TX_2056_ptr = regs_TX_2056_rev5;
			regs_RX_2056_ptr = regs_RX_2056_rev5;
			break;

		case 6:
			regs_SYN_2056_ptr = regs_SYN_2056_rev6;
			regs_TX_2056_ptr = regs_TX_2056_rev6;
			regs_RX_2056_ptr = regs_RX_2056_rev6;
			break;

		case 7:
		case 9:
			regs_SYN_2056_ptr = regs_SYN_2056_rev7;
			regs_TX_2056_ptr = regs_TX_2056_rev7;
			regs_RX_2056_ptr = regs_RX_2056_rev7;
			break;

		case 8:
			regs_SYN_2056_ptr = regs_SYN_2056_rev8;
			regs_TX_2056_ptr = regs_TX_2056_rev8;
			regs_RX_2056_ptr = regs_RX_2056_rev8;
			break;

		case 11:
			regs_SYN_2056_ptr = regs_SYN_2056_rev11;
			regs_TX_2056_ptr = regs_TX_2056_rev11;
			regs_RX_2056_ptr = regs_RX_2056_rev11;
			break;

		default:
			return;
		}
	}

	wlc_phy_init_radio_regs(pi, regs_SYN_2056_ptr, (u16) RADIO_2056_SYN);

	wlc_phy_init_radio_regs(pi, regs_TX_2056_ptr, (u16) RADIO_2056_TX0);

	wlc_phy_init_radio_regs(pi, regs_TX_2056_ptr, (u16) RADIO_2056_TX1);

	wlc_phy_init_radio_regs(pi, regs_RX_2056_ptr, (u16) RADIO_2056_RX0);

	wlc_phy_init_radio_regs(pi, regs_RX_2056_ptr, (u16) RADIO_2056_RX1);
}