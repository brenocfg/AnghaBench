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
 int /*<<< orphan*/  OHCI1394_PhyControl_Read (int) ; 
 int OHCI1394_PhyControl_ReadData (int) ; 
 int OHCI1394_PhyControl_ReadDone ; 
 int /*<<< orphan*/  dump_stack () ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  ohci_err (struct fw_ohci*,char*,int) ; 
 int reg_read (struct fw_ohci*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_write (struct fw_ohci*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int read_phy_reg(struct fw_ohci *ohci, int addr)
{
	u32 val;
	int i;

	reg_write(ohci, OHCI1394_PhyControl, OHCI1394_PhyControl_Read(addr));
	for (i = 0; i < 3 + 100; i++) {
		val = reg_read(ohci, OHCI1394_PhyControl);
		if (!~val)
			return -ENODEV; /* Card was ejected. */

		if (val & OHCI1394_PhyControl_ReadDone)
			return OHCI1394_PhyControl_ReadData(val);

		/*
		 * Try a few times without waiting.  Sleeping is necessary
		 * only when the link/PHY interface is busy.
		 */
		if (i >= 3)
			msleep(1);
	}
	ohci_err(ohci, "failed to read phy reg %d\n", addr);
	dump_stack();

	return -EBUSY;
}