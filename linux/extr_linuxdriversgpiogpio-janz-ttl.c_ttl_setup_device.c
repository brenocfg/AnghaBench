#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ttl_module {TYPE_1__* regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  portc; int /*<<< orphan*/  portb; int /*<<< orphan*/  porta; int /*<<< orphan*/  control; } ;

/* Variables and functions */
 int CONF_PAE ; 
 int CONF_PBE ; 
 int CONF_PCE ; 
 int /*<<< orphan*/  MASTER_CONF_CTL ; 
 int /*<<< orphan*/  PORTA_DIRECTION ; 
 int /*<<< orphan*/  PORTA_IOCTL ; 
 int /*<<< orphan*/  PORTB_DIRECTION ; 
 int /*<<< orphan*/  PORTB_IOCTL ; 
 int /*<<< orphan*/  PORTC_DIRECTION ; 
 int /*<<< orphan*/  PORTC_IOCTL ; 
 int /*<<< orphan*/  iowrite16be (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttl_write_reg (struct ttl_module*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ttl_setup_device(struct ttl_module *mod)
{
	/* reset the device to a known state */
	iowrite16be(0x0000, &mod->regs->control);
	iowrite16be(0x0001, &mod->regs->control);
	iowrite16be(0x0000, &mod->regs->control);

	/* put all ports in open-drain mode */
	ttl_write_reg(mod, PORTA_IOCTL, 0x00ff);
	ttl_write_reg(mod, PORTB_IOCTL, 0x00ff);
	ttl_write_reg(mod, PORTC_IOCTL, 0x000f);

	/* set all ports as outputs */
	ttl_write_reg(mod, PORTA_DIRECTION, 0x0000);
	ttl_write_reg(mod, PORTB_DIRECTION, 0x0000);
	ttl_write_reg(mod, PORTC_DIRECTION, 0x0000);

	/* set all ports to drive zeroes */
	iowrite16be(0x0000, &mod->regs->porta);
	iowrite16be(0x0000, &mod->regs->portb);
	iowrite16be(0x0000, &mod->regs->portc);

	/* enable all ports */
	ttl_write_reg(mod, MASTER_CONF_CTL, CONF_PAE | CONF_PBE | CONF_PCE);
}