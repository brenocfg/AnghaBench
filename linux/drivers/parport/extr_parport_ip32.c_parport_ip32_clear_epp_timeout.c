#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  dsr; } ;
struct parport_ip32_private {TYPE_2__ regs; } ;
struct parport {TYPE_1__* physport; } ;
struct TYPE_3__ {struct parport_ip32_private* private_data; } ;

/* Variables and functions */
 unsigned int DSR_TIMEOUT ; 
 unsigned int parport_ip32_read_status (struct parport*) ; 
 int /*<<< orphan*/  pr_trace (struct parport*,char*,char*) ; 
 int /*<<< orphan*/  writeb (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int parport_ip32_clear_epp_timeout(struct parport *p)
{
	struct parport_ip32_private * const priv = p->physport->private_data;
	unsigned int cleared;

	if (!(parport_ip32_read_status(p) & DSR_TIMEOUT))
		cleared = 1;
	else {
		unsigned int r;
		/* To clear timeout some chips require double read */
		parport_ip32_read_status(p);
		r = parport_ip32_read_status(p);
		/* Some reset by writing 1 */
		writeb(r | DSR_TIMEOUT, priv->regs.dsr);
		/* Others by writing 0 */
		writeb(r & ~DSR_TIMEOUT, priv->regs.dsr);

		r = parport_ip32_read_status(p);
		cleared = !(r & DSR_TIMEOUT);
	}

	pr_trace(p, "(): %s", cleared ? "cleared" : "failed");
	return cleared;
}