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
typedef  int u32 ;
struct fw_ohci {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int /*<<< orphan*/  OHCI1394_PhyControl ; 
 int /*<<< orphan*/  OHCI1394_PhyControl_Write (int,int) ; 
 int OHCI1394_PhyControl_WritePending ; 
 int /*<<< orphan*/  dump_stack () ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  ohci_err (struct fw_ohci const*,char*,int,int) ; 
 int reg_read (struct fw_ohci const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_write (struct fw_ohci const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int write_phy_reg(const struct fw_ohci *ohci, int addr, u32 val)
{
	int i;

	reg_write(ohci, OHCI1394_PhyControl,
		  OHCI1394_PhyControl_Write(addr, val));
	for (i = 0; i < 3 + 100; i++) {
		val = reg_read(ohci, OHCI1394_PhyControl);
		if (!~val)
			return -ENODEV; /* Card was ejected. */

		if (!(val & OHCI1394_PhyControl_WritePending))
			return 0;

		if (i >= 3)
			msleep(1);
	}
	ohci_err(ohci, "failed to write phy reg %d, val %u\n", addr, val);
	dump_stack();

	return -EBUSY;
}