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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct nvkm_udevice {int /*<<< orphan*/  device; } ;
struct nvkm_object {int dummy; } ;

/* Variables and functions */
 struct nvkm_udevice* nvkm_udevice (struct nvkm_object*) ; 
 int /*<<< orphan*/  nvkm_wr08 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nvkm_udevice_wr08(struct nvkm_object *object, u64 addr, u8 data)
{
	struct nvkm_udevice *udev = nvkm_udevice(object);
	nvkm_wr08(udev->device, addr, data);
	return 0;
}