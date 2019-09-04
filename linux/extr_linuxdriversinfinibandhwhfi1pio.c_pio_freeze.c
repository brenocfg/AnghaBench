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
struct send_context {int flags; scalar_t__ type; } ;
struct hfi1_devdata {int num_send_contexts; TYPE_1__* send_contexts; } ;
struct TYPE_2__ {struct send_context* sc; } ;

/* Variables and functions */
 int SCF_FROZEN ; 
 scalar_t__ SC_USER ; 
 int /*<<< orphan*/  sc_disable (struct send_context*) ; 

void pio_freeze(struct hfi1_devdata *dd)
{
	struct send_context *sc;
	int i;

	for (i = 0; i < dd->num_send_contexts; i++) {
		sc = dd->send_contexts[i].sc;
		/*
		 * Don't disable unallocated, unfrozen, or user send contexts.
		 * User send contexts will be disabled when the process
		 * calls into the driver to reset its context.
		 */
		if (!sc || !(sc->flags & SCF_FROZEN) || sc->type == SC_USER)
			continue;

		/* only need to disable, the context is already stopped */
		sc_disable(sc);
	}
}