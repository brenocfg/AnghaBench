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
typedef  int u32 ;
struct nvkm_subdev {struct nvkm_device* device; } ;
struct nvkm_ltc {struct nvkm_subdev subdev; } ;
struct nvkm_device {int dummy; } ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int /*<<< orphan*/  gf100_ltc_lts_intr_name ; 
 int /*<<< orphan*/  nvkm_error (struct nvkm_subdev*,char*,int,int,int,char*) ; 
 int nvkm_rd32 (struct nvkm_device*,int) ; 
 int /*<<< orphan*/  nvkm_snprintbf (char*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int,int) ; 

__attribute__((used)) static void
gf100_ltc_lts_intr(struct nvkm_ltc *ltc, int c, int s)
{
	struct nvkm_subdev *subdev = &ltc->subdev;
	struct nvkm_device *device = subdev->device;
	u32 base = 0x141000 + (c * 0x2000) + (s * 0x400);
	u32 intr = nvkm_rd32(device, base + 0x020);
	u32 stat = intr & 0x0000ffff;
	char msg[128];

	if (stat) {
		nvkm_snprintbf(msg, sizeof(msg), gf100_ltc_lts_intr_name, stat);
		nvkm_error(subdev, "LTC%d_LTS%d: %08x [%s]\n", c, s, stat, msg);
	}

	nvkm_wr32(device, base + 0x020, intr);
}