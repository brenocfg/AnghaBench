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
typedef  int u_char ;
struct scr24x_dev {scalar_t__ regs; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ SCR24X_CMD_STATUS ; 
 int STATUS_BUSY ; 
 int ioread8 (scalar_t__) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int scr24x_wait_ready(struct scr24x_dev *dev)
{
	u_char status;
	int timeout = 100;

	do {
		status = ioread8(dev->regs + SCR24X_CMD_STATUS);
		if (!(status & STATUS_BUSY))
			return 0;

		msleep(20);
	} while (--timeout);

	return -EIO;
}