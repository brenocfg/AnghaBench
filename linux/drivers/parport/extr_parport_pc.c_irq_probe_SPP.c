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
 int PARPORT_IRQ_NONE ; 

__attribute__((used)) static int irq_probe_SPP(struct parport *pb)
{
	/* Don't even try to do this. */
	return PARPORT_IRQ_NONE;
}