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
struct de_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BusMode ; 
 int /*<<< orphan*/  CmdReset ; 
 int EBUSY ; 
 int ENODEV ; 
 int /*<<< orphan*/  MacStatus ; 
 int RxState ; 
 int TxState ; 
 int /*<<< orphan*/  de_bus_mode ; 
 int dr32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dw32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static int de_reset_mac (struct de_private *de)
{
	u32 status, tmp;

	/*
	 * Reset MAC.  de4x5.c and tulip.c examined for "advice"
	 * in this area.
	 */

	if (dr32(BusMode) == 0xffffffff)
		return -EBUSY;

	/* Reset the chip, holding bit 0 set at least 50 PCI cycles. */
	dw32 (BusMode, CmdReset);
	mdelay (1);

	dw32 (BusMode, de_bus_mode);
	mdelay (1);

	for (tmp = 0; tmp < 5; tmp++) {
		dr32 (BusMode);
		mdelay (1);
	}

	mdelay (1);

	status = dr32(MacStatus);
	if (status & (RxState | TxState))
		return -EBUSY;
	if (status == 0xffffffff)
		return -ENODEV;
	return 0;
}