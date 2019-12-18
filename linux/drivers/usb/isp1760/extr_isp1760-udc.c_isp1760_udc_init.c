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
typedef  int u16 ;
struct isp1760_udc {TYPE_1__* isp; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_CHIPID ; 
 int /*<<< orphan*/  DC_MODE ; 
 int /*<<< orphan*/  DC_SCRATCH ; 
 int DC_SFRESET ; 
 int ENODEV ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,...) ; 
 int isp1760_udc_read (struct isp1760_udc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isp1760_udc_write (struct isp1760_udc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int isp1760_udc_init(struct isp1760_udc *udc)
{
	u16 scratch;
	u32 chipid;

	/*
	 * Check that the controller is present by writing to the scratch
	 * register, modifying the bus pattern by reading from the chip ID
	 * register, and reading the scratch register value back. The chip ID
	 * and scratch register contents must match the expected values.
	 */
	isp1760_udc_write(udc, DC_SCRATCH, 0xbabe);
	chipid = isp1760_udc_read(udc, DC_CHIPID);
	scratch = isp1760_udc_read(udc, DC_SCRATCH);

	if (scratch != 0xbabe) {
		dev_err(udc->isp->dev,
			"udc: scratch test failed (0x%04x/0x%08x)\n",
			scratch, chipid);
		return -ENODEV;
	}

	if (chipid != 0x00011582 && chipid != 0x00158210) {
		dev_err(udc->isp->dev, "udc: invalid chip ID 0x%08x\n", chipid);
		return -ENODEV;
	}

	/* Reset the device controller. */
	isp1760_udc_write(udc, DC_MODE, DC_SFRESET);
	usleep_range(10000, 11000);
	isp1760_udc_write(udc, DC_MODE, 0);
	usleep_range(10000, 11000);

	return 0;
}