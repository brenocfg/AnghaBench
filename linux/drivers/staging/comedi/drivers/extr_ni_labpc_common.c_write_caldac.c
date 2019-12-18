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
struct labpc_private {int cmd5; int /*<<< orphan*/  (* write_byte ) (struct comedi_device*,int,int /*<<< orphan*/ ) ;} ;
struct comedi_device {struct labpc_private* private; } ;

/* Variables and functions */
 int CMD5_CALDACLD ; 
 int CMD5_EEPROMCS ; 
 int /*<<< orphan*/  CMD5_REG ; 
 int CMD5_WRTPRT ; 
 int /*<<< orphan*/  labpc_serial_out (struct comedi_device*,unsigned int,int) ; 
 int /*<<< orphan*/  stub1 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void write_caldac(struct comedi_device *dev, unsigned int channel,
			 unsigned int value)
{
	struct labpc_private *devpriv = dev->private;

	/*  clear caldac load bit and make sure we don't write to eeprom */
	devpriv->cmd5 &= ~(CMD5_CALDACLD | CMD5_EEPROMCS | CMD5_WRTPRT);
	udelay(1);
	devpriv->write_byte(dev, devpriv->cmd5, CMD5_REG);

	/*  write 4 bit channel */
	labpc_serial_out(dev, channel, 4);
	/*  write 8 bit caldac value */
	labpc_serial_out(dev, value, 8);

	/*  set and clear caldac bit to load caldac value */
	devpriv->cmd5 |= CMD5_CALDACLD;
	udelay(1);
	devpriv->write_byte(dev, devpriv->cmd5, CMD5_REG);
	devpriv->cmd5 &= ~CMD5_CALDACLD;
	udelay(1);
	devpriv->write_byte(dev, devpriv->cmd5, CMD5_REG);
}