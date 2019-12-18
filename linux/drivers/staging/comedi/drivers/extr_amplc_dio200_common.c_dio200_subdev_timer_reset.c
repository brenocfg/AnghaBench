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
 int /*<<< orphan*/  DIO200_TS_CONFIG ; 
 unsigned int TS_CONFIG_CLK_SRC_MASK ; 
 unsigned int TS_CONFIG_RESET ; 
 unsigned int dio200_read32 (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dio200_write32 (struct comedi_device*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void dio200_subdev_timer_reset(struct comedi_device *dev,
				      struct comedi_subdevice *s)
{
	unsigned int clock;

	clock = dio200_read32(dev, DIO200_TS_CONFIG) & TS_CONFIG_CLK_SRC_MASK;
	dio200_write32(dev, DIO200_TS_CONFIG, clock | TS_CONFIG_RESET);
	dio200_write32(dev, DIO200_TS_CONFIG, clock);
}