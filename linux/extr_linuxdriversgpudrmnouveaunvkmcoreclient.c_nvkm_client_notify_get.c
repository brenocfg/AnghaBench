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
struct nvkm_client {TYPE_1__** notify; } ;
struct TYPE_2__ {int /*<<< orphan*/  n; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__**) ; 
 int ENOENT ; 
 int /*<<< orphan*/  nvkm_notify_get (int /*<<< orphan*/ *) ; 

int
nvkm_client_notify_get(struct nvkm_client *client, int index)
{
	if (index < ARRAY_SIZE(client->notify)) {
		if (client->notify[index]) {
			nvkm_notify_get(&client->notify[index]->n);
			return 0;
		}
	}
	return -ENOENT;
}