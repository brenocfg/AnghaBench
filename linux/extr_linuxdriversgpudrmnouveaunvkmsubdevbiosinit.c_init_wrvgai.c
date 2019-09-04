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
typedef  int u8 ;
typedef  int u16 ;
struct nvkm_device {scalar_t__ card_type; } ;
struct nvbios_init {int head; TYPE_1__* subdev; } ;
struct TYPE_2__ {struct nvkm_device* device; } ;

/* Variables and functions */
 scalar_t__ NV_50 ; 
 scalar_t__ init_exec (struct nvbios_init*) ; 
 int /*<<< orphan*/  nvkm_wrvgai (struct nvkm_device*,int,int,int,int) ; 

__attribute__((used)) static void
init_wrvgai(struct nvbios_init *init, u16 port, u8 index, u8 value)
{
	struct nvkm_device *device = init->subdev->device;

	/* force head 0 for updates to cr44, it only exists on first head */
	if (device->card_type < NV_50) {
		if (port == 0x03d4 && index == 0x44)
			init->head = 0;
	}

	if (init_exec(init)) {
		int head = init->head < 0 ? 0 : init->head;
		nvkm_wrvgai(device, head, port, index, value);
	}

	/* select head 1 if cr44 write selected it */
	if (device->card_type < NV_50) {
		if (port == 0x03d4 && index == 0x44 && value == 3)
			init->head = 1;
	}
}