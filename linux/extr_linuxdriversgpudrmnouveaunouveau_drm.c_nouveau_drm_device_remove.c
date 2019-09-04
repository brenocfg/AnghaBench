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
struct nvkm_device {int dummy; } ;
struct nvkm_client {int /*<<< orphan*/  device; } ;
struct TYPE_2__ {int /*<<< orphan*/  base; } ;
struct nouveau_drm {TYPE_1__ client; } ;
struct drm_device {int irq_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_put_dev (struct drm_device*) ; 
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 
 int /*<<< orphan*/  nvkm_device_del (struct nvkm_device**) ; 
 struct nvkm_device* nvkm_device_find (int /*<<< orphan*/ ) ; 
 struct nvkm_client* nvxx_client (int /*<<< orphan*/ *) ; 

void
nouveau_drm_device_remove(struct drm_device *dev)
{
	struct nouveau_drm *drm = nouveau_drm(dev);
	struct nvkm_client *client;
	struct nvkm_device *device;

	dev->irq_enabled = false;
	client = nvxx_client(&drm->client.base);
	device = nvkm_device_find(client->device);
	drm_put_dev(dev);

	nvkm_device_del(&device);
}