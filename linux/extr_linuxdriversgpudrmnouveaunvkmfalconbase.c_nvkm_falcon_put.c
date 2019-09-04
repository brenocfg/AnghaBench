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
struct nvkm_subdev {int dummy; } ;
struct nvkm_falcon {int /*<<< orphan*/  mutex; struct nvkm_subdev const* user; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvkm_debug (struct nvkm_subdev const*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

void
nvkm_falcon_put(struct nvkm_falcon *falcon, const struct nvkm_subdev *user)
{
	if (unlikely(!falcon))
		return;

	mutex_lock(&falcon->mutex);
	if (falcon->user == user) {
		nvkm_debug(falcon->user, "released %s falcon\n", falcon->name);
		falcon->user = NULL;
	}
	mutex_unlock(&falcon->mutex);
}