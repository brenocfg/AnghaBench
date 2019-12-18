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
struct parport {int modes; scalar_t__ irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECONTROL (struct parport*) ; 
 int /*<<< orphan*/  ECR_WRITE (struct parport*,unsigned char) ; 
 int PARPORT_IRQ_NONE ; 
 int PARPORT_MODE_PCECR ; 
 int /*<<< orphan*/  clear_epp_timeout (struct parport*) ; 
 int /*<<< orphan*/  frob_econtrol (struct parport*,int,int) ; 
 unsigned char inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parport_pc_frob_control (struct parport*,int,int) ; 
 int /*<<< orphan*/  parport_pc_read_epp (struct parport*) ; 
 int /*<<< orphan*/  parport_pc_write_control (struct parport*,int) ; 
 scalar_t__ probe_irq_off (int) ; 
 int probe_irq_on () ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int irq_probe_EPP(struct parport *pb)
{
#ifndef ADVANCED_DETECT
	return PARPORT_IRQ_NONE;
#else
	int irqs;
	unsigned char oecr;

	if (pb->modes & PARPORT_MODE_PCECR)
		oecr = inb(ECONTROL(pb));

	irqs = probe_irq_on();

	if (pb->modes & PARPORT_MODE_PCECR)
		frob_econtrol(pb, 0x10, 0x10);

	clear_epp_timeout(pb);
	parport_pc_frob_control(pb, 0x20, 0x20);
	parport_pc_frob_control(pb, 0x10, 0x10);
	clear_epp_timeout(pb);

	/* Device isn't expecting an EPP read
	 * and generates an IRQ.
	 */
	parport_pc_read_epp(pb);
	udelay(20);

	pb->irq = probe_irq_off(irqs);
	if (pb->modes & PARPORT_MODE_PCECR)
		ECR_WRITE(pb, oecr);
	parport_pc_write_control(pb, 0xc);

	if (pb->irq <= 0)
		pb->irq = PARPORT_IRQ_NONE;

	return pb->irq;
#endif /* Advanced detection */
}