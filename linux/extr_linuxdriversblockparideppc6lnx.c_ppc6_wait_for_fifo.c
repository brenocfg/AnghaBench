#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int ppc_flags; scalar_t__ lpt_addr; } ;
typedef  TYPE_1__ Interface ;

/* Variables and functions */
 int fifo_wait ; 
 int /*<<< orphan*/  inb (scalar_t__) ; 

__attribute__((used)) static void ppc6_wait_for_fifo(Interface *ppc)
{
	int i;

	if (ppc->ppc_flags & fifo_wait)
	{
		for(i=0; i<20; i++)
			inb(ppc->lpt_addr + 1);
	}
}