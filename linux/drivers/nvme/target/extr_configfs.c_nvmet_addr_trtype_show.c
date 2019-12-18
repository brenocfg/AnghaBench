#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ trtype; } ;
struct nvmet_port {TYPE_1__ disc_addr; } ;
struct config_item {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_5__ {scalar_t__ type; char* name; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_2__*) ; 
 TYPE_2__* nvmet_transport_names ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 struct nvmet_port* to_nvmet_port (struct config_item*) ; 

__attribute__((used)) static ssize_t nvmet_addr_trtype_show(struct config_item *item,
		char *page)
{
	struct nvmet_port *port = to_nvmet_port(item);
	int i;

	for (i = 0; i < ARRAY_SIZE(nvmet_transport_names); i++) {
		if (port->disc_addr.trtype != nvmet_transport_names[i].type)
			continue;
		return sprintf(page, "%s\n", nvmet_transport_names[i].name);
	}

	return sprintf(page, "\n");
}