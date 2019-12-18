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
struct comedi_subdevice {int dummy; } ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIO200_CLK_SCE (unsigned int) ; 
 int /*<<< orphan*/  clk_gat_sce (unsigned int,unsigned int,unsigned int) ; 
 unsigned int dio200_subdev_8254_offset (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  dio200_write8 (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dio200_subdev_8254_set_clock_src(struct comedi_device *dev,
					     struct comedi_subdevice *s,
					     unsigned int chan,
					     unsigned int src)
{
	unsigned int offset = dio200_subdev_8254_offset(dev, s);

	dio200_write8(dev, DIO200_CLK_SCE(offset >> 3),
		      clk_gat_sce((offset >> 2) & 1, chan, src));
}