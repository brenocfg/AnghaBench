#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct nvkm_subdev {struct nvkm_device* device; } ;
struct nvkm_device {int /*<<< orphan*/  cfgopt; struct nvkm_clk* clk; struct nvkm_bios* bios; } ;
struct nvkm_clk {int dummy; } ;
struct nvkm_bios {int dummy; } ;
struct nvbios_M0205T {scalar_t__ freq; int /*<<< orphan*/  member_0; } ;
struct gt215_ramfuc {int dummy; } ;
struct TYPE_6__ {TYPE_4__* fb; TYPE_1__* func; } ;
struct gt215_ltrain {int r_100720; int r_1111e0; int r_111400; int /*<<< orphan*/  state; } ;
struct gt215_ram {TYPE_2__ base; struct gt215_ramfuc fuc; struct gt215_ltrain ltrain; } ;
struct TYPE_7__ {struct nvkm_subdev subdev; } ;
struct TYPE_5__ {int (* calc ) (TYPE_2__*,int) ;} ;

/* Variables and functions */
 int EBUSY ; 
 int ENOENT ; 
 int ENOMEM ; 
 int ENOSYS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NVA3_TRAIN_DONE ; 
 int /*<<< orphan*/  NVA3_TRAIN_EXEC ; 
 int /*<<< orphan*/  NVA3_TRAIN_UNSUPPORTED ; 
 int /*<<< orphan*/  gt215_clk_post (struct nvkm_clk*,unsigned long*) ; 
 int gt215_clk_pre (struct nvkm_clk*,unsigned long*) ; 
 int /*<<< orphan*/  gt215_link_train_calc (int*,struct gt215_ltrain*) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv_clk_src_mem ; 
 int /*<<< orphan*/  nvbios_M0205Tp (struct nvkm_bios*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct nvbios_M0205T*) ; 
 int nvkm_boolopt (int /*<<< orphan*/ ,char*,int) ; 
 unsigned int nvkm_clk_read (struct nvkm_clk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_debug (struct nvkm_subdev*,char*,int,...) ; 
 int /*<<< orphan*/  nvkm_mask (struct nvkm_device*,int,int,int) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int,int) ; 
 int /*<<< orphan*/  ram_exec (struct gt215_ramfuc*,int) ; 
 int /*<<< orphan*/  ram_mask (struct gt215_ramfuc*,int,int,int) ; 
 int /*<<< orphan*/  ram_nsec (struct gt215_ramfuc*,int) ; 
 int /*<<< orphan*/  ram_nuke (struct gt215_ramfuc*,int) ; 
 int ram_rd32 (struct gt215_ramfuc*,int) ; 
 int /*<<< orphan*/  ram_train (struct gt215_ramfuc*) ; 
 int /*<<< orphan*/  ram_train_result (TYPE_4__*,int*,int) ; 
 int /*<<< orphan*/  ram_wait (struct gt215_ramfuc*,int,int,int,int) ; 
 int /*<<< orphan*/  ram_wait_vblank (struct gt215_ramfuc*) ; 
 int /*<<< orphan*/  ram_wr32 (struct gt215_ramfuc*,int,int) ; 
 int stub1 (TYPE_2__*,int) ; 
 int stub2 (TYPE_2__*,unsigned int) ; 

__attribute__((used)) static int
gt215_link_train(struct gt215_ram *ram)
{
	struct gt215_ltrain *train = &ram->ltrain;
	struct gt215_ramfuc *fuc = &ram->fuc;
	struct nvkm_subdev *subdev = &ram->base.fb->subdev;
	struct nvkm_device *device = subdev->device;
	struct nvkm_bios *bios = device->bios;
	struct nvkm_clk *clk = device->clk;
	u32 *result, r1700;
	int ret, i;
	struct nvbios_M0205T M0205T = { 0 };
	u8 ver, hdr, cnt, len, snr, ssz;
	unsigned int clk_current;
	unsigned long flags;
	unsigned long *f = &flags;

	if (nvkm_boolopt(device->cfgopt, "NvMemExec", true) != true)
		return -ENOSYS;

	/* XXX: Multiple partitions? */
	result = kmalloc_array(64, sizeof(u32), GFP_KERNEL);
	if (!result)
		return -ENOMEM;

	train->state = NVA3_TRAIN_EXEC;

	/* Clock speeds for training and back */
	nvbios_M0205Tp(bios, &ver, &hdr, &cnt, &len, &snr, &ssz, &M0205T);
	if (M0205T.freq == 0) {
		kfree(result);
		return -ENOENT;
	}

	clk_current = nvkm_clk_read(clk, nv_clk_src_mem);

	ret = gt215_clk_pre(clk, f);
	if (ret)
		goto out;

	/* First: clock up/down */
	ret = ram->base.func->calc(&ram->base, (u32) M0205T.freq * 1000);
	if (ret)
		goto out;

	/* Do this *after* calc, eliminates write in script */
	nvkm_wr32(device, 0x111400, 0x00000000);
	/* XXX: Magic writes that improve train reliability? */
	nvkm_mask(device, 0x100674, 0x0000ffff, 0x00000000);
	nvkm_mask(device, 0x1005e4, 0x0000ffff, 0x00000000);
	nvkm_mask(device, 0x100b0c, 0x000000ff, 0x00000000);
	nvkm_wr32(device, 0x100c04, 0x00000400);

	/* Now the training script */
	r1700 = ram_rd32(fuc, 0x001700);

	ram_mask(fuc, 0x100200, 0x00000800, 0x00000000);
	ram_wr32(fuc, 0x611200, 0x3300);
	ram_wait_vblank(fuc);
	ram_wait(fuc, 0x611200, 0x00000003, 0x00000000, 500000);
	ram_mask(fuc, 0x001610, 0x00000083, 0x00000003);
	ram_mask(fuc, 0x100080, 0x00000020, 0x00000000);
	ram_mask(fuc, 0x10f804, 0x80000000, 0x00000000);
	ram_wr32(fuc, 0x001700, 0x00000000);

	ram_train(fuc);

	/* Reset */
	ram_mask(fuc, 0x10f804, 0x80000000, 0x80000000);
	ram_wr32(fuc, 0x10053c, 0x0);
	ram_wr32(fuc, 0x100720, train->r_100720);
	ram_wr32(fuc, 0x1111e0, train->r_1111e0);
	ram_wr32(fuc, 0x111400, train->r_111400);
	ram_nuke(fuc, 0x100080);
	ram_mask(fuc, 0x100080, 0x00000020, 0x00000020);
	ram_nsec(fuc, 1000);

	ram_wr32(fuc, 0x001700, r1700);
	ram_mask(fuc, 0x001610, 0x00000083, 0x00000080);
	ram_wr32(fuc, 0x611200, 0x3330);
	ram_mask(fuc, 0x100200, 0x00000800, 0x00000800);

	ram_exec(fuc, true);

	ram->base.func->calc(&ram->base, clk_current);
	ram_exec(fuc, true);

	/* Post-processing, avoids flicker */
	nvkm_mask(device, 0x616308, 0x10, 0x10);
	nvkm_mask(device, 0x616b08, 0x10, 0x10);

	gt215_clk_post(clk, f);

	ram_train_result(ram->base.fb, result, 64);
	for (i = 0; i < 64; i++)
		nvkm_debug(subdev, "Train: %08x", result[i]);
	gt215_link_train_calc(result, train);

	nvkm_debug(subdev, "Train: %08x %08x %08x", train->r_100720,
		   train->r_1111e0, train->r_111400);

	kfree(result);

	train->state = NVA3_TRAIN_DONE;

	return ret;

out:
	if(ret == -EBUSY)
		f = NULL;

	train->state = NVA3_TRAIN_UNSUPPORTED;

	gt215_clk_post(clk, f);
	kfree(result);
	return ret;
}