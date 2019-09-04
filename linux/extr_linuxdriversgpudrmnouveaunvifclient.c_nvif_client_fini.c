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
struct TYPE_4__ {int /*<<< orphan*/  priv; } ;
struct nvif_client {TYPE_1__* driver; TYPE_2__ object; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* fini ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  nvif_object_fini (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void
nvif_client_fini(struct nvif_client *client)
{
	nvif_object_fini(&client->object);
	if (client->driver) {
		if (client->driver->fini)
			client->driver->fini(client->object.priv);
		client->driver = NULL;
	}
}