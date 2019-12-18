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
struct TYPE_4__ {int /*<<< orphan*/  dcr; } ;
struct parport_ip32_private {unsigned int dcr_writable; unsigned int dcr_cache; TYPE_2__ regs; } ;
struct parport {TYPE_1__* physport; } ;
struct TYPE_3__ {struct parport_ip32_private* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_EXTRA_BITS (struct parport*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  writeb (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void __parport_ip32_write_control(struct parport *p,
						unsigned int c)
{
	struct parport_ip32_private * const priv = p->physport->private_data;
	CHECK_EXTRA_BITS(p, c, priv->dcr_writable);
	c &= priv->dcr_writable; /* only writable bits */
	writeb(c, priv->regs.dcr);
	priv->dcr_cache = c;		/* update soft copy */
}