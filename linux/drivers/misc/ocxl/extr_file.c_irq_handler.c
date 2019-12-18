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
struct eventfd_ctx {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  eventfd_signal (struct eventfd_ctx*,int) ; 

__attribute__((used)) static irqreturn_t irq_handler(void *private)
{
	struct eventfd_ctx *ev_ctx = private;

	eventfd_signal(ev_ctx, 1);
	return IRQ_HANDLED;
}