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
struct amo {int dummy; } ;
struct TYPE_2__ {struct amo* amos_page; } ;

/* Variables and functions */
 int /*<<< orphan*/  xpc_receive_IRQ_amo_sn2 (struct amo*) ; 
 TYPE_1__* xpc_vars_sn2 ; 

__attribute__((used)) static struct amo *
xpc_init_IRQ_amo_sn2(int index)
{
	struct amo *amo = xpc_vars_sn2->amos_page + index;

	(void)xpc_receive_IRQ_amo_sn2(amo);	/* clear amo variable */
	return amo;
}