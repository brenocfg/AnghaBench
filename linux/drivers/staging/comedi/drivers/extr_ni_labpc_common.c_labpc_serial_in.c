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
struct labpc_private {int stat2; int (* read_byte ) (struct comedi_device*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  cmd5; int /*<<< orphan*/  (* write_byte ) (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct comedi_device {struct labpc_private* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD5_REG ; 
 int /*<<< orphan*/  CMD5_SCLK ; 
 int STAT2_PROMOUT ; 
 int /*<<< orphan*/  STAT2_REG ; 
 int /*<<< orphan*/  stub1 (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub3 (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static unsigned int labpc_serial_in(struct comedi_device *dev)
{
	struct labpc_private *devpriv = dev->private;
	unsigned int value = 0;
	int i;
	const int value_width = 8;	/*  number of bits wide values are */

	for (i = 1; i <= value_width; i++) {
		/*  set serial clock */
		devpriv->cmd5 |= CMD5_SCLK;
		udelay(1);
		devpriv->write_byte(dev, devpriv->cmd5, CMD5_REG);
		/*  clear clock bit */
		devpriv->cmd5 &= ~CMD5_SCLK;
		udelay(1);
		devpriv->write_byte(dev, devpriv->cmd5, CMD5_REG);
		/*  read bits most significant bit first */
		udelay(1);
		devpriv->stat2 = devpriv->read_byte(dev, STAT2_REG);
		if (devpriv->stat2 & STAT2_PROMOUT)
			value |= 1 << (value_width - i);
	}

	return value;
}