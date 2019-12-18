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
struct nvkm_subdev {size_t index; } ;
struct nvkm_falcon {int /*<<< orphan*/  mutex; struct nvkm_subdev const* user; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvkm_debug (struct nvkm_subdev const*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_error (struct nvkm_subdev const*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * nvkm_subdev_name ; 

int
nvkm_falcon_get(struct nvkm_falcon *falcon, const struct nvkm_subdev *user)
{
	mutex_lock(&falcon->mutex);
	if (falcon->user) {
		nvkm_error(user, "%s falcon already acquired by %s!\n",
			   falcon->name, nvkm_subdev_name[falcon->user->index]);
		mutex_unlock(&falcon->mutex);
		return -EBUSY;
	}

	nvkm_debug(user, "acquired %s falcon\n", falcon->name);
	falcon->user = user;
	mutex_unlock(&falcon->mutex);
	return 0;
}