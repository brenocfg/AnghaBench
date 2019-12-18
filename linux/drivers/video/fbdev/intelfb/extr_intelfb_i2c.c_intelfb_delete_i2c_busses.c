#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct intelfb_info {TYPE_3__* output; } ;
struct TYPE_5__ {int /*<<< orphan*/ * dinfo; int /*<<< orphan*/  adapter; } ;
struct TYPE_4__ {int /*<<< orphan*/ * dinfo; int /*<<< orphan*/  adapter; } ;
struct TYPE_6__ {TYPE_2__ ddc_bus; TYPE_1__ i2c_bus; } ;

/* Variables and functions */
 int MAX_OUTPUTS ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 

void intelfb_delete_i2c_busses(struct intelfb_info *dinfo)
{
	int i;

	for (i = 0; i < MAX_OUTPUTS; i++) {
		if (dinfo->output[i].i2c_bus.dinfo) {
			i2c_del_adapter(&dinfo->output[i].i2c_bus.adapter);
			dinfo->output[i].i2c_bus.dinfo = NULL;
		}
		if (dinfo->output[i].ddc_bus.dinfo) {
			i2c_del_adapter(&dinfo->output[i].ddc_bus.adapter);
			dinfo->output[i].ddc_bus.dinfo = NULL;
		}
	}
}