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
 int Z8536_CMD_CLR_IE ; 
 int /*<<< orphan*/  Z8536_INT_CTRL_REG ; 
 int /*<<< orphan*/  Z8536_PA_CMDSTAT_REG ; 
 int /*<<< orphan*/  Z8536_PB_CMDSTAT_REG ; 
 int /*<<< orphan*/  apci1500_ack_irq (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apci1500_port_enable (struct comedi_device*,int) ; 
 int /*<<< orphan*/  z8536_write (struct comedi_device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int apci1500_di_cancel(struct comedi_device *dev,
			      struct comedi_subdevice *s)
{
	/* Disables the main interrupt on the board */
	z8536_write(dev, 0x00, Z8536_INT_CTRL_REG);

	/* Disable Ports A & B */
	apci1500_port_enable(dev, false);

	/* Ack any pending interrupts */
	apci1500_ack_irq(dev, Z8536_PA_CMDSTAT_REG);
	apci1500_ack_irq(dev, Z8536_PB_CMDSTAT_REG);

	/* Disable pattern interrupts */
	z8536_write(dev, Z8536_CMD_CLR_IE, Z8536_PA_CMDSTAT_REG);
	z8536_write(dev, Z8536_CMD_CLR_IE, Z8536_PB_CMDSTAT_REG);

	/* Enable Ports A & B */
	apci1500_port_enable(dev, true);

	return 0;
}