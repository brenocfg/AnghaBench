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
struct TYPE_3__ {int ctr; int ecr; } ;
struct TYPE_4__ {TYPE_1__ pc; } ;
struct parport_state {TYPE_2__ u; } ;
struct pardevice {scalar_t__ irq_func; } ;

/* Variables and functions */

__attribute__((used)) static void parport_uss720_init_state(struct pardevice *dev, struct parport_state *s)
{
	s->u.pc.ctr = 0xc | (dev->irq_func ? 0x10 : 0x0);
	s->u.pc.ecr = 0x24;
}