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
struct parport {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIGB (struct parport*) ; 
 int /*<<< orphan*/  ECONTROL (struct parport*) ; 
 int ECR_CNF ; 
 int /*<<< orphan*/  ECR_WRITE (struct parport*,unsigned char) ; 
#define  PARPORT_IRQ_NONE 128 
 int inb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int programmable_irq_support(struct parport *pb)
{
	int irq, intrLine;
	unsigned char oecr = inb(ECONTROL(pb));
	static const int lookup[8] = {
		PARPORT_IRQ_NONE, 7, 9, 10, 11, 14, 15, 5
	};

	ECR_WRITE(pb, ECR_CNF << 5); /* Configuration MODE */

	intrLine = (inb(CONFIGB(pb)) >> 3) & 0x07;
	irq = lookup[intrLine];

	ECR_WRITE(pb, oecr);
	return irq;
}