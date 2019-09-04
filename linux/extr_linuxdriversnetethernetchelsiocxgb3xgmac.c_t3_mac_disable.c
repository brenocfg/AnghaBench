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
struct cmac {scalar_t__ offset; struct adapter* adapter; scalar_t__ txen; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 scalar_t__ A_XGM_RESET_CTRL ; 
 scalar_t__ A_XGM_RX_CTRL ; 
 scalar_t__ A_XGM_TX_CTRL ; 
 int F_MAC_RESET_ ; 
 int F_PCS_RESET_ ; 
 int F_RGMII_RESET_ ; 
 int F_XG2G_RESET_ ; 
 int MAC_DIRECTION_RX ; 
 int MAC_DIRECTION_TX ; 
 scalar_t__ is_10G (struct adapter*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  t3_set_reg_field (struct adapter*,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t3_write_reg (struct adapter*,scalar_t__,int) ; 
 scalar_t__ uses_xaui (struct adapter*) ; 

int t3_mac_disable(struct cmac *mac, int which)
{
	struct adapter *adap = mac->adapter;

	if (which & MAC_DIRECTION_TX) {
		t3_write_reg(adap, A_XGM_TX_CTRL + mac->offset, 0);
		mac->txen = 0;
	}
	if (which & MAC_DIRECTION_RX) {
		int val = F_MAC_RESET_;

		t3_set_reg_field(mac->adapter, A_XGM_RESET_CTRL + mac->offset,
				 F_PCS_RESET_, 0);
		msleep(100);
		t3_write_reg(adap, A_XGM_RX_CTRL + mac->offset, 0);
		if (is_10G(adap))
			val |= F_PCS_RESET_;
		else if (uses_xaui(adap))
			val |= F_PCS_RESET_ | F_XG2G_RESET_;
		else
			val |= F_RGMII_RESET_ | F_XG2G_RESET_;
		t3_write_reg(mac->adapter, A_XGM_RESET_CTRL + mac->offset, val);
	}
	return 0;
}