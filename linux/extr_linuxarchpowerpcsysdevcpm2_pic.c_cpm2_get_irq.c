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
struct TYPE_2__ {int /*<<< orphan*/  ic_sivec; } ;

/* Variables and functions */
 TYPE_1__* cpm2_intctl ; 
 int /*<<< orphan*/  cpm2_pic_host ; 
 unsigned long in_be32 (int /*<<< orphan*/ *) ; 
 unsigned int irq_linear_revmap (int /*<<< orphan*/ ,int) ; 

unsigned int cpm2_get_irq(void)
{
	int irq;
	unsigned long bits;

       /* For CPM2, read the SIVEC register and shift the bits down
         * to get the irq number.         */
        bits = in_be32(&cpm2_intctl->ic_sivec);
        irq = bits >> 26;

	if (irq == 0)
		return(-1);
	return irq_linear_revmap(cpm2_pic_host, irq);
}