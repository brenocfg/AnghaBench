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
struct parport_pc_private {int ecr; } ;
struct parport {struct parport_pc_private* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONTROL (struct parport*) ; 
 int /*<<< orphan*/  ECONTROL (struct parport*) ; 
 int /*<<< orphan*/  ECR_SPP ; 
 int /*<<< orphan*/  ECR_WRITE (struct parport*,int) ; 
 int /*<<< orphan*/  frob_set_mode (struct parport*,int /*<<< orphan*/ ) ; 
 int inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parport_ECR_present(struct parport *pb)
{
	struct parport_pc_private *priv = pb->private_data;
	unsigned char r = 0xc;

	outb(r, CONTROL(pb));
	if ((inb(ECONTROL(pb)) & 0x3) == (r & 0x3)) {
		outb(r ^ 0x2, CONTROL(pb)); /* Toggle bit 1 */

		r = inb(CONTROL(pb));
		if ((inb(ECONTROL(pb)) & 0x2) == (r & 0x2))
			goto no_reg; /* Sure that no ECR register exists */
	}

	if ((inb(ECONTROL(pb)) & 0x3) != 0x1)
		goto no_reg;

	ECR_WRITE(pb, 0x34);
	if (inb(ECONTROL(pb)) != 0x35)
		goto no_reg;

	priv->ecr = 1;
	outb(0xc, CONTROL(pb));

	/* Go to mode 000 */
	frob_set_mode(pb, ECR_SPP);

	return 1;

 no_reg:
	outb(0xc, CONTROL(pb));
	return 0;
}