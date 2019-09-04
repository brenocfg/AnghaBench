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
struct scr24x_dev {scalar_t__ regs; int /*<<< orphan*/ * buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_READ_BYTE ; 
 scalar_t__ SCR24X_CMD_STATUS ; 
 scalar_t__ SCR24X_DATA (size_t) ; 
 int /*<<< orphan*/  ioread8 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite8 (int /*<<< orphan*/ ,scalar_t__) ; 
 int scr24x_wait_ready (struct scr24x_dev*) ; 

__attribute__((used)) static int read_chunk(struct scr24x_dev *dev, size_t offset, size_t limit)
{
	size_t i, y;
	int ret;

	for (i = offset; i < limit; i += 5) {
		iowrite8(CMD_READ_BYTE, dev->regs + SCR24X_CMD_STATUS);
		ret = scr24x_wait_ready(dev);
		if (ret < 0)
			return ret;

		for (y = 0; y < 5 && i + y < limit; y++)
			dev->buf[i + y] = ioread8(dev->regs + SCR24X_DATA(y));
	}

	return 0;
}