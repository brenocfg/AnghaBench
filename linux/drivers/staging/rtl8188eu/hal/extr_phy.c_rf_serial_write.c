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
typedef  int u32 ;
struct bb_reg_def {int /*<<< orphan*/  rf3wireOffset; } ;
struct adapter {TYPE_1__* HalData; } ;
typedef  enum rf_radio_path { ____Placeholder_rf_radio_path } rf_radio_path ;
struct TYPE_2__ {struct bb_reg_def* PHYRegDef; } ;

/* Variables and functions */
 int /*<<< orphan*/  bMaskDWord ; 
 int /*<<< orphan*/  phy_set_bb_reg (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rf_serial_write(struct adapter *adapt,
			    enum rf_radio_path rfpath, u32 offset,
			    u32 data)
{
	u32 data_and_addr = 0;
	struct bb_reg_def *phyreg = &adapt->HalData->PHYRegDef[rfpath];

	offset &= 0xff;
	data_and_addr = ((offset<<20) | (data&0x000fffff)) & 0x0fffffff;
	phy_set_bb_reg(adapt, phyreg->rf3wireOffset, bMaskDWord, data_and_addr);
}