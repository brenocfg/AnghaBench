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
struct comedi_device {int /*<<< orphan*/  class_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  NI67XX_CAL_CMD_REG ; 
 int NI67XX_CAL_STATUS_BUSY ; 
 int /*<<< orphan*/  NI67XX_CAL_STATUS_REG ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int ni_ao_win_inw (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ni_ao_win_outw (struct comedi_device*,unsigned short,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void cs5529_command(struct comedi_device *dev, unsigned short value)
{
	static const int timeout = 100;
	int i;

	ni_ao_win_outw(dev, value, NI67XX_CAL_CMD_REG);
	/* give time for command to start being serially clocked into cs5529.
	 * this insures that the NI67XX_CAL_STATUS_BUSY bit will get properly
	 * set before we exit this function.
	 */
	for (i = 0; i < timeout; i++) {
		if (ni_ao_win_inw(dev, NI67XX_CAL_STATUS_REG) &
		    NI67XX_CAL_STATUS_BUSY)
			break;
		udelay(1);
	}
	if (i == timeout)
		dev_err(dev->class_dev,
			"possible problem - never saw adc go busy?\n");
}