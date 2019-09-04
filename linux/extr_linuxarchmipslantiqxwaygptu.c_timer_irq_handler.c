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
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int start; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPTU_IRNCR ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  gptu_w32 (int,int /*<<< orphan*/ ) ; 
 TYPE_1__* irqres ; 

__attribute__((used)) static irqreturn_t timer_irq_handler(int irq, void *priv)
{
	int timer = irq - irqres[0].start;
	gptu_w32(1 << timer, GPTU_IRNCR);
	return IRQ_HANDLED;
}