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
struct subdev_8255_private {unsigned long regbase; int /*<<< orphan*/  (* io ) (struct comedi_device*,int,int /*<<< orphan*/ ,int,unsigned long) ;} ;
struct comedi_subdevice {int io_bits; struct subdev_8255_private* private; } ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 int I8255_CTRL_A_IO ; 
 int I8255_CTRL_B_IO ; 
 int I8255_CTRL_CW ; 
 int I8255_CTRL_C_HI_IO ; 
 int I8255_CTRL_C_LO_IO ; 
 int /*<<< orphan*/  I8255_CTRL_REG ; 
 int /*<<< orphan*/  stub1 (struct comedi_device*,int,int /*<<< orphan*/ ,int,unsigned long) ; 

__attribute__((used)) static void subdev_8255_do_config(struct comedi_device *dev,
				  struct comedi_subdevice *s)
{
	struct subdev_8255_private *spriv = s->private;
	unsigned long regbase = spriv->regbase;
	int config;

	config = I8255_CTRL_CW;
	/* 1 in io_bits indicates output, 1 in config indicates input */
	if (!(s->io_bits & 0x0000ff))
		config |= I8255_CTRL_A_IO;
	if (!(s->io_bits & 0x00ff00))
		config |= I8255_CTRL_B_IO;
	if (!(s->io_bits & 0x0f0000))
		config |= I8255_CTRL_C_LO_IO;
	if (!(s->io_bits & 0xf00000))
		config |= I8255_CTRL_C_HI_IO;

	spriv->io(dev, 1, I8255_CTRL_REG, config, regbase);
}