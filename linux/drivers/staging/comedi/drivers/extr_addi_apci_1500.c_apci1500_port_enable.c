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
 unsigned int Z8536_CFG_CTRL_PAE ; 
 unsigned int Z8536_CFG_CTRL_PBE ; 
 int /*<<< orphan*/  Z8536_CFG_CTRL_REG ; 
 unsigned int z8536_read (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  z8536_write (struct comedi_device*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void apci1500_port_enable(struct comedi_device *dev, bool enable)
{
	unsigned int cfg;

	cfg = z8536_read(dev, Z8536_CFG_CTRL_REG);
	if (enable)
		cfg |= (Z8536_CFG_CTRL_PAE | Z8536_CFG_CTRL_PBE);
	else
		cfg &= ~(Z8536_CFG_CTRL_PAE | Z8536_CFG_CTRL_PBE);
	z8536_write(dev, cfg, Z8536_CFG_CTRL_REG);
}