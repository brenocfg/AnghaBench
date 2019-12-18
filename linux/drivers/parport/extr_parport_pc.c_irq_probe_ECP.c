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
struct parport {int irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECONTROL (struct parport*) ; 
 int ECR_SPP ; 
 int ECR_TST ; 
 int /*<<< orphan*/  ECR_WRITE (struct parport*,int) ; 
 int /*<<< orphan*/  FIFO (struct parport*) ; 
 int PARPORT_IRQ_NONE ; 
 int inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 int probe_irq_off (unsigned long) ; 
 unsigned long probe_irq_on () ; 

__attribute__((used)) static int irq_probe_ECP(struct parport *pb)
{
	int i;
	unsigned long irqs;

	irqs = probe_irq_on();

	ECR_WRITE(pb, ECR_SPP << 5); /* Reset FIFO */
	ECR_WRITE(pb, (ECR_TST << 5) | 0x04);
	ECR_WRITE(pb, ECR_TST << 5);

	/* If Full FIFO sure that writeIntrThreshold is generated */
	for (i = 0; i < 1024 && !(inb(ECONTROL(pb)) & 0x02) ; i++)
		outb(0xaa, FIFO(pb));

	pb->irq = probe_irq_off(irqs);
	ECR_WRITE(pb, ECR_SPP << 5);

	if (pb->irq <= 0)
		pb->irq = PARPORT_IRQ_NONE;

	return pb->irq;
}