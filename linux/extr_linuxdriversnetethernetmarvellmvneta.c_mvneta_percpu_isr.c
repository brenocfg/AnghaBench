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
struct mvneta_pcpu_port {int /*<<< orphan*/  napi; TYPE_2__* pp; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {TYPE_1__* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  disable_percpu_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t mvneta_percpu_isr(int irq, void *dev_id)
{
	struct mvneta_pcpu_port *port = (struct mvneta_pcpu_port *)dev_id;

	disable_percpu_irq(port->pp->dev->irq);
	napi_schedule(&port->napi);

	return IRQ_HANDLED;
}