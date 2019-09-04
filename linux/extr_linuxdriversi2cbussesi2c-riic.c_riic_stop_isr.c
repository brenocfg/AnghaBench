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
struct riic_dev {int /*<<< orphan*/  msg_done; scalar_t__ base; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ RIIC_ICIER ; 
 scalar_t__ RIIC_ICSR2 ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  readb (scalar_t__) ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static irqreturn_t riic_stop_isr(int irq, void *data)
{
	struct riic_dev *riic = data;

	/* read back registers to confirm writes have fully propagated */
	writeb(0, riic->base + RIIC_ICSR2);
	readb(riic->base + RIIC_ICSR2);
	writeb(0, riic->base + RIIC_ICIER);
	readb(riic->base + RIIC_ICIER);

	complete(&riic->msg_done);

	return IRQ_HANDLED;
}