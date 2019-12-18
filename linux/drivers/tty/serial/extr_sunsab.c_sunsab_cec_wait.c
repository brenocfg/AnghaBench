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
struct uart_sunsab_port {int cec_timeout; TYPE_2__* regs; } ;
struct TYPE_3__ {int /*<<< orphan*/  star; } ;
struct TYPE_4__ {TYPE_1__ r; } ;

/* Variables and functions */
 int SAB82532_STAR_CEC ; 
 int readb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static __inline__ void sunsab_cec_wait(struct uart_sunsab_port *up)
{
	int timeout = up->cec_timeout;

	while ((readb(&up->regs->r.star) & SAB82532_STAR_CEC) && --timeout)
		udelay(1);
}