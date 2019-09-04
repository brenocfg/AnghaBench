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
struct TYPE_2__ {struct nvkm_device* device; } ;
struct nvkm_engine {TYPE_1__ subdev; } ;
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int,int) ; 

__attribute__((used)) static int
g84_cipher_init(struct nvkm_engine *cipher)
{
	struct nvkm_device *device = cipher->subdev.device;
	nvkm_wr32(device, 0x102130, 0xffffffff);
	nvkm_wr32(device, 0x102140, 0xffffffbf);
	nvkm_wr32(device, 0x10200c, 0x00000010);
	return 0;
}