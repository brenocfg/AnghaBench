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
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_XGM_RGMII_IMP ; 
 int /*<<< orphan*/  A_XGM_XAUI_IMP ; 
 int /*<<< orphan*/  CH_ERR (struct adapter*,char*) ; 
 unsigned int F_CALBUSY ; 
 unsigned int F_XGM_CALFAULT ; 
 int /*<<< orphan*/  F_XGM_IMPSETUPDATE ; 
 int G_CALIMP (unsigned int) ; 
 int V_RGMIIIMPPD (int) ; 
 int V_RGMIIIMPPU (int) ; 
 int V_XAUIIMP (int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 unsigned int t3_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t3_set_reg_field (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t3_write_reg (struct adapter*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ uses_xaui (struct adapter*) ; 

__attribute__((used)) static int calibrate_xgm(struct adapter *adapter)
{
	if (uses_xaui(adapter)) {
		unsigned int v, i;

		for (i = 0; i < 5; ++i) {
			t3_write_reg(adapter, A_XGM_XAUI_IMP, 0);
			t3_read_reg(adapter, A_XGM_XAUI_IMP);
			msleep(1);
			v = t3_read_reg(adapter, A_XGM_XAUI_IMP);
			if (!(v & (F_XGM_CALFAULT | F_CALBUSY))) {
				t3_write_reg(adapter, A_XGM_XAUI_IMP,
					     V_XAUIIMP(G_CALIMP(v) >> 2));
				return 0;
			}
		}
		CH_ERR(adapter, "MAC calibration failed\n");
		return -1;
	} else {
		t3_write_reg(adapter, A_XGM_RGMII_IMP,
			     V_RGMIIIMPPD(2) | V_RGMIIIMPPU(3));
		t3_set_reg_field(adapter, A_XGM_RGMII_IMP, F_XGM_IMPSETUPDATE,
				 F_XGM_IMPSETUPDATE);
	}
	return 0;
}