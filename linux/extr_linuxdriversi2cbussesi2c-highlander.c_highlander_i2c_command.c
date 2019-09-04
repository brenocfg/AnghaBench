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
typedef  int u8 ;
typedef  int u16 ;
struct highlander_i2c_dev {int /*<<< orphan*/  dev; scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ SMSADR ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,int) ; 
 int /*<<< orphan*/  iowrite16 (int,scalar_t__) ; 

__attribute__((used)) static void highlander_i2c_command(struct highlander_i2c_dev *dev,
				   u8 command, int len)
{
	unsigned int i;
	u16 cmd = (command << 8) | command;

	for (i = 0; i < len; i += 2) {
		if (len - i == 1)
			cmd = command << 8;
		iowrite16(cmd, dev->base + SMSADR + i);
		dev_dbg(dev->dev, "command data[%x] 0x%04x\n", i/2, cmd);
	}
}