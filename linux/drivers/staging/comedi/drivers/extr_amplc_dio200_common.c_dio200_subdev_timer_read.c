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
struct comedi_insn {unsigned int n; } ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIO200_TS_COUNT ; 
 unsigned int dio200_read32 (struct comedi_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dio200_subdev_timer_read(struct comedi_device *dev,
				    struct comedi_subdevice *s,
				    struct comedi_insn *insn,
				    unsigned int *data)
{
	unsigned int n;

	for (n = 0; n < insn->n; n++)
		data[n] = dio200_read32(dev, DIO200_TS_COUNT);
	return n;
}