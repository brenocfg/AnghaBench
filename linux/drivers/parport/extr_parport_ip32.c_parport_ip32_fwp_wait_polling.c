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
struct parport_ip32_private {unsigned int fifo_depth; } ;
struct parport {TYPE_1__* cad; struct parport* physport; struct parport_ip32_private* private_data; } ;
struct TYPE_2__ {unsigned long timeout; } ;

/* Variables and functions */
 unsigned int ECR_F_EMPTY ; 
 int /*<<< orphan*/  FIFO_POLLING_INTERVAL ; 
 unsigned long jiffies ; 
 scalar_t__ parport_ip32_fifo_wait_break (struct parport*,unsigned long) ; 
 unsigned int parport_ip32_read_econtrol (struct parport*) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int parport_ip32_fwp_wait_polling(struct parport *p)
{
	struct parport_ip32_private * const priv = p->physport->private_data;
	struct parport * const physport = p->physport;
	unsigned long expire;
	unsigned int count;
	unsigned int ecr;

	expire = jiffies + physport->cad->timeout;
	count = 0;
	while (1) {
		if (parport_ip32_fifo_wait_break(p, expire))
			break;

		/* Check FIFO state.  We do nothing when the FIFO is nor full,
		 * nor empty.  It appears that the FIFO full bit is not always
		 * reliable, the FIFO state is sometimes wrongly reported, and
		 * the chip gets confused if we give it another byte. */
		ecr = parport_ip32_read_econtrol(p);
		if (ecr & ECR_F_EMPTY) {
			/* FIFO is empty, fill it up */
			count = priv->fifo_depth;
			break;
		}

		/* Wait a moment... */
		udelay(FIFO_POLLING_INTERVAL);
	} /* while (1) */

	return count;
}