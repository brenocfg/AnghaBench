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
struct TYPE_2__ {int cs; } ;

/* Variables and functions */
 TYPE_1__* at93c ; 
 int at93c_reg_read () ; 
 int /*<<< orphan*/  at93c_reg_write (int) ; 
 int /*<<< orphan*/  lasat_ndelay (int) ; 

__attribute__((used)) static void at93c_end_op(void)
{
	at93c_reg_write(at93c_reg_read() & ~at93c->cs);
	lasat_ndelay(250);
}