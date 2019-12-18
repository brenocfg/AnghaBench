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
struct cdns3 {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  cdns3_hw_role_switch (struct cdns3*) ; 

__attribute__((used)) static irqreturn_t cdns3_drd_thread_irq(int irq, void *data)
{
	struct cdns3 *cdns = data;

	cdns3_hw_role_switch(cdns);

	return IRQ_HANDLED;
}