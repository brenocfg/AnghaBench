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
struct ci_hdrc {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  OP_USBCMD ; 
 int /*<<< orphan*/  USBCMD_RST ; 
 scalar_t__ hw_read (struct ci_hdrc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_write (struct ci_hdrc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int hw_controller_reset(struct ci_hdrc *ci)
{
	int count = 0;

	hw_write(ci, OP_USBCMD, USBCMD_RST, USBCMD_RST);
	while (hw_read(ci, OP_USBCMD, USBCMD_RST)) {
		udelay(10);
		if (count++ > 1000)
			return -ETIMEDOUT;
	}

	return 0;
}