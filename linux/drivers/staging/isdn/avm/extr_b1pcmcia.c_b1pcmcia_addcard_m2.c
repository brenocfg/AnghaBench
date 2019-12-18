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

/* Variables and functions */
 int /*<<< orphan*/  avm_m2 ; 
 int b1pcmcia_add_card (unsigned int,unsigned int,int /*<<< orphan*/ ) ; 

int b1pcmcia_addcard_m2(unsigned int port, unsigned irq)
{
	return b1pcmcia_add_card(port, irq, avm_m2);
}