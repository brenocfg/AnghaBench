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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_3__ {int /*<<< orphan*/  priv; } ;
struct nvif_client {TYPE_1__ object; TYPE_2__* driver; } ;
struct TYPE_4__ {int (* init ) (char const*,int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* fini ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 int nvif_client_init (struct nvif_client*,char const*,int /*<<< orphan*/ ,struct nvif_client*) ; 
 TYPE_2__** nvif_driver ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 
 int stub1 (char const*,int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 

int
nvif_driver_init(const char *drv, const char *cfg, const char *dbg,
		 const char *name, u64 device, struct nvif_client *client)
{
	int ret = -EINVAL, i;

	for (i = 0; (client->driver = nvif_driver[i]); i++) {
		if (!drv || !strcmp(client->driver->name, drv)) {
			ret = client->driver->init(name, device, cfg, dbg,
						   &client->object.priv);
			if (ret == 0)
				break;
			client->driver->fini(client->object.priv);
		}
	}

	if (ret == 0)
		ret = nvif_client_init(client, name, device, client);
	return ret;
}