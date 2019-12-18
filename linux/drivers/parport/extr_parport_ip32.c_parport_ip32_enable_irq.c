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
 int /*<<< orphan*/  DCR_IRQ ; 
 int /*<<< orphan*/  __parport_ip32_frob_control (struct parport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void parport_ip32_enable_irq(struct parport *p)
{
	__parport_ip32_frob_control(p, DCR_IRQ, DCR_IRQ);
}