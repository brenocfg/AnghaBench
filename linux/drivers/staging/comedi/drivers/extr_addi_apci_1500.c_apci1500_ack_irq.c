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
struct comedi_device {int dummy; } ;

/* Variables and functions */
 unsigned int Z8536_CMD_CLR_IP_IUS ; 
 unsigned int Z8536_STAT_IE_IP ; 
 unsigned int z8536_read (struct comedi_device*,unsigned int) ; 
 int /*<<< orphan*/  z8536_write (struct comedi_device*,unsigned int,unsigned int) ; 

__attribute__((used)) static bool apci1500_ack_irq(struct comedi_device *dev,
			     unsigned int reg)
{
	unsigned int val;

	val = z8536_read(dev, reg);
	if ((val & Z8536_STAT_IE_IP) == Z8536_STAT_IE_IP) {
		val &= 0x0f;			/* preserve any write bits */
		val |= Z8536_CMD_CLR_IP_IUS;
		z8536_write(dev, val, reg);

		return true;
	}
	return false;
}