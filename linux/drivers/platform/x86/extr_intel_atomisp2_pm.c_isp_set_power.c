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
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_MBI_UNIT_PMC ; 
 int EBUSY ; 
 int /*<<< orphan*/  ISPSSPM0 ; 
 int /*<<< orphan*/  ISPSSPM0_ISPSSC_MASK ; 
 int ISPSSPM0_ISPSSS_MASK ; 
 int ISPSSPM0_ISPSSS_OFFSET ; 
 int ISPSSPM0_IUNIT_POWER_OFF ; 
 int ISPSSPM0_IUNIT_POWER_ON ; 
 int /*<<< orphan*/  MBI_REG_READ ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  iosf_mbi_modify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iosf_mbi_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int isp_set_power(struct pci_dev *dev, bool enable)
{
	unsigned long timeout;
	u32 val = enable ? ISPSSPM0_IUNIT_POWER_ON :
		ISPSSPM0_IUNIT_POWER_OFF;

	/* Write to ISPSSPM0 bit[1:0] to power on/off the IUNIT */
	iosf_mbi_modify(BT_MBI_UNIT_PMC, MBI_REG_READ, ISPSSPM0,
			val, ISPSSPM0_ISPSSC_MASK);

	/*
	 * There should be no IUNIT access while power-down is
	 * in progress HW sighting: 4567865
	 * Wait up to 50 ms for the IUNIT to shut down.
	 * And we do the same for power on.
	 */
	timeout = jiffies + msecs_to_jiffies(50);
	while (1) {
		u32 tmp;

		/* Wait until ISPSSPM0 bit[25:24] shows the right value */
		iosf_mbi_read(BT_MBI_UNIT_PMC, MBI_REG_READ, ISPSSPM0, &tmp);
		tmp = (tmp & ISPSSPM0_ISPSSS_MASK) >> ISPSSPM0_ISPSSS_OFFSET;
		if (tmp == val)
			break;

		if (time_after(jiffies, timeout)) {
			dev_err(&dev->dev, "IUNIT power-%s timeout.\n",
				enable ? "on" : "off");
			return -EBUSY;
		}
		usleep_range(1000, 2000);
	}

	return 0;
}