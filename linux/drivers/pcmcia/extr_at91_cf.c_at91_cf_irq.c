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
struct at91_cf_socket {unsigned int present; int /*<<< orphan*/  socket; TYPE_2__* pdev; TYPE_1__* board; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  det_pin; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  SS_DETECT ; 
 unsigned int at91_cf_present (struct at91_cf_socket*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,char*) ; 
 int gpio_to_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcmcia_parse_events (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t at91_cf_irq(int irq, void *_cf)
{
	struct at91_cf_socket *cf = _cf;

	if (irq == gpio_to_irq(cf->board->det_pin)) {
		unsigned present = at91_cf_present(cf);

		/* kick pccard as needed */
		if (present != cf->present) {
			cf->present = present;
			dev_dbg(&cf->pdev->dev, "card %s\n",
					present ? "present" : "gone");
			pcmcia_parse_events(&cf->socket, SS_DETECT);
		}
	}

	return IRQ_HANDLED;
}