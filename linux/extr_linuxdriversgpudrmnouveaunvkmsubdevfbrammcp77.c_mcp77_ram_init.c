#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct nvkm_ram {int dummy; } ;
struct nvkm_device {int dummy; } ;
struct TYPE_6__ {int size; TYPE_2__* fb; } ;
struct mcp77_ram {int poller_base; TYPE_3__ base; } ;
struct TYPE_4__ {struct nvkm_device* device; } ;
struct TYPE_5__ {TYPE_1__ subdev; } ;

/* Variables and functions */
 struct mcp77_ram* mcp77_ram (struct nvkm_ram*) ; 
 int /*<<< orphan*/  nvkm_mask (struct nvkm_device*,int,int,int) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int,int) ; 

__attribute__((used)) static int
mcp77_ram_init(struct nvkm_ram *base)
{
	struct mcp77_ram *ram = mcp77_ram(base);
	struct nvkm_device *device = ram->base.fb->subdev.device;
	u32 dniso  = ((ram->base.size - (ram->poller_base + 0x00)) >> 5) - 1;
	u32 hostnb = ((ram->base.size - (ram->poller_base + 0x20)) >> 5) - 1;
	u32 flush  = ((ram->base.size - (ram->poller_base + 0x40)) >> 5) - 1;

	/* Enable NISO poller for various clients and set their associated
	 * read address, only for MCP77/78 and MCP79/7A. (fd#27501)
	 */
	nvkm_wr32(device, 0x100c18, dniso);
	nvkm_mask(device, 0x100c14, 0x00000000, 0x00000001);
	nvkm_wr32(device, 0x100c1c, hostnb);
	nvkm_mask(device, 0x100c14, 0x00000000, 0x00000002);
	nvkm_wr32(device, 0x100c24, flush);
	nvkm_mask(device, 0x100c14, 0x00000000, 0x00010000);
	return 0;
}