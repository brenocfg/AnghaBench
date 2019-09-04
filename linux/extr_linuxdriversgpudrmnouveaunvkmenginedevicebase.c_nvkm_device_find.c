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
typedef  int /*<<< orphan*/  u64 ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nv_devices_mutex ; 
 struct nvkm_device* nvkm_device_find_locked (int /*<<< orphan*/ ) ; 

struct nvkm_device *
nvkm_device_find(u64 handle)
{
	struct nvkm_device *device;
	mutex_lock(&nv_devices_mutex);
	device = nvkm_device_find_locked(handle);
	mutex_unlock(&nv_devices_mutex);
	return device;
}