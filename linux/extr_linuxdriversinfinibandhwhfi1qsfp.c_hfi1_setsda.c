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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct hfi1_i2c_bus {int /*<<< orphan*/  num; struct hfi1_devdata* controlling_dd; } ;
struct hfi1_devdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  QSFP_HFI0_I2CDAT ; 
 int /*<<< orphan*/  i2c_oe_csr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_csr (struct hfi1_devdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_csr (struct hfi1_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hfi1_setsda(void *data, int state)
{
	struct hfi1_i2c_bus *bus = (struct hfi1_i2c_bus *)data;
	struct hfi1_devdata *dd = bus->controlling_dd;
	u64 reg;
	u32 target_oe;

	target_oe = i2c_oe_csr(bus->num);
	reg = read_csr(dd, target_oe);
	/*
	 * The OE bit value is inverted and connected to the pin.  When
	 * OE is 0 the pin is left to be pulled up, when the OE is 1
	 * the pin is driven low.  This matches the "open drain" or "open
	 * collector" convention.
	 */
	if (state)
		reg &= ~QSFP_HFI0_I2CDAT;
	else
		reg |= QSFP_HFI0_I2CDAT;
	write_csr(dd, target_oe, reg);
	/* do a read to force the write into the chip */
	(void)read_csr(dd, target_oe);
}