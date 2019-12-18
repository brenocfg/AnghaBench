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
struct coresight_platform_data {int nr_outport; TYPE_1__* conns; } ;
struct TYPE_2__ {int /*<<< orphan*/ * child_fwnode; } ;

/* Variables and functions */
 int /*<<< orphan*/  fwnode_handle_put (int /*<<< orphan*/ *) ; 

void coresight_release_platform_data(struct coresight_platform_data *pdata)
{
	int i;

	for (i = 0; i < pdata->nr_outport; i++) {
		if (pdata->conns[i].child_fwnode) {
			fwnode_handle_put(pdata->conns[i].child_fwnode);
			pdata->conns[i].child_fwnode = NULL;
		}
	}
}