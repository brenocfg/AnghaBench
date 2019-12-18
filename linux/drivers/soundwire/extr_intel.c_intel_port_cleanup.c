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
struct sdw_cdns_dma_data {int nr_ports; TYPE_2__** port; } ;
struct TYPE_4__ {int assigned; TYPE_1__* pdi; } ;
struct TYPE_3__ {int assigned; } ;

/* Variables and functions */

__attribute__((used)) static void intel_port_cleanup(struct sdw_cdns_dma_data *dma)
{
	int i;

	for (i = 0; i < dma->nr_ports; i++) {
		if (dma->port[i]) {
			dma->port[i]->pdi->assigned = false;
			dma->port[i]->pdi = NULL;
			dma->port[i]->assigned = false;
			dma->port[i] = NULL;
		}
	}
}