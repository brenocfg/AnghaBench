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
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ANAPAR_FOR_8192PciE ; 
 int BIT4 ; 
 int /*<<< orphan*/  rFPGA0_AnalogParameter1 ; 
 int /*<<< orphan*/  rFPGA0_AnalogParameter4 ; 
 int /*<<< orphan*/  rFPGA0_XA_RFInterfaceOE ; 
 int /*<<< orphan*/  rOFDM0_TRxPathEnable ; 
 int /*<<< orphan*/  rOFDM1_TRxPathEnable ; 
 int /*<<< orphan*/  rtl92e_set_bb_reg (struct net_device*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  rtl92e_writeb (struct net_device*,int /*<<< orphan*/ ,int) ; 

void rtl92e_set_rf_off(struct net_device *dev)
{

	rtl92e_set_bb_reg(dev, rFPGA0_XA_RFInterfaceOE, BIT4, 0x0);
	rtl92e_set_bb_reg(dev, rFPGA0_AnalogParameter4, 0x300, 0x0);
	rtl92e_set_bb_reg(dev, rFPGA0_AnalogParameter1, 0x18, 0x0);
	rtl92e_set_bb_reg(dev, rOFDM0_TRxPathEnable, 0xf, 0x0);
	rtl92e_set_bb_reg(dev, rOFDM1_TRxPathEnable, 0xf, 0x0);
	rtl92e_set_bb_reg(dev, rFPGA0_AnalogParameter1, 0x60, 0x0);
	rtl92e_set_bb_reg(dev, rFPGA0_AnalogParameter1, 0x4, 0x0);
	rtl92e_writeb(dev, ANAPAR_FOR_8192PciE, 0x07);

}