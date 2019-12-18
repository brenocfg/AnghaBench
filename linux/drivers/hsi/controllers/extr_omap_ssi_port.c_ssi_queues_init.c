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
struct omap_ssi_port {int /*<<< orphan*/  brkqueue; int /*<<< orphan*/ * rxqueue; int /*<<< orphan*/ * txqueue; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 unsigned int SSI_MAX_CHANNELS ; 

__attribute__((used)) static void ssi_queues_init(struct omap_ssi_port *omap_port)
{
	unsigned int ch;

	for (ch = 0; ch < SSI_MAX_CHANNELS; ch++) {
		INIT_LIST_HEAD(&omap_port->txqueue[ch]);
		INIT_LIST_HEAD(&omap_port->rxqueue[ch]);
	}
	INIT_LIST_HEAD(&omap_port->brkqueue);
}