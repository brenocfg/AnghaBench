#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct pnp_dev {struct pnp_card_link* card_link; } ;
struct TYPE_6__ {scalar_t__ event; } ;
struct pnp_card_link {TYPE_1__* driver; TYPE_2__ pm_state; } ;
typedef  TYPE_2__ pm_message_t ;
struct TYPE_5__ {int (* suspend ) (struct pnp_card_link*,TYPE_2__) ;} ;

/* Variables and functions */
 int stub1 (struct pnp_card_link*,TYPE_2__) ; 

__attribute__((used)) static int card_suspend(struct pnp_dev *dev, pm_message_t state)
{
	struct pnp_card_link *link = dev->card_link;

	if (link->pm_state.event == state.event)
		return 0;
	link->pm_state = state;
	return link->driver->suspend(link, state);
}