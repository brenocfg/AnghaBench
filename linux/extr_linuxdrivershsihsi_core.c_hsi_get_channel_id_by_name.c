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
struct TYPE_4__ {int num_channels; TYPE_1__* channels; } ;
struct hsi_client {TYPE_2__ rx_cfg; } ;
struct TYPE_3__ {int id; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENXIO ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

int hsi_get_channel_id_by_name(struct hsi_client *cl, char *name)
{
	int i;

	if (!cl->rx_cfg.channels)
		return -ENOENT;

	for (i = 0; i < cl->rx_cfg.num_channels; i++)
		if (!strcmp(cl->rx_cfg.channels[i].name, name))
			return cl->rx_cfg.channels[i].id;

	return -ENXIO;
}