#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_44__   TYPE_9__ ;
typedef  struct TYPE_43__   TYPE_8__ ;
typedef  struct TYPE_42__   TYPE_7__ ;
typedef  struct TYPE_41__   TYPE_6__ ;
typedef  struct TYPE_40__   TYPE_5__ ;
typedef  struct TYPE_39__   TYPE_4__ ;
typedef  struct TYPE_38__   TYPE_3__ ;
typedef  struct TYPE_37__   TYPE_2__ ;
typedef  struct TYPE_36__   TYPE_22__ ;
typedef  struct TYPE_35__   TYPE_21__ ;
typedef  struct TYPE_34__   TYPE_20__ ;
typedef  struct TYPE_33__   TYPE_1__ ;
typedef  struct TYPE_32__   TYPE_19__ ;
typedef  struct TYPE_31__   TYPE_18__ ;
typedef  struct TYPE_30__   TYPE_17__ ;
typedef  struct TYPE_29__   TYPE_16__ ;
typedef  struct TYPE_28__   TYPE_15__ ;
typedef  struct TYPE_27__   TYPE_14__ ;
typedef  struct TYPE_26__   TYPE_13__ ;
typedef  struct TYPE_25__   TYPE_12__ ;
typedef  struct TYPE_24__   TYPE_11__ ;
typedef  struct TYPE_23__   TYPE_10__ ;

/* Type definitions */
struct nvkm_subdev {int dummy; } ;
struct nvkm_engine {struct nvkm_subdev subdev; } ;
struct nvkm_device {unsigned long long disable_mask; TYPE_22__* volt; TYPE_21__* top; TYPE_20__* timer; TYPE_19__* therm; TYPE_18__* secboot; TYPE_17__* pmu; TYPE_16__* pci; struct nvkm_subdev* mxm; TYPE_15__* mmu; TYPE_14__* mc; TYPE_13__* ltc; TYPE_12__* imem; TYPE_11__* iccsense; struct nvkm_subdev* ibus; TYPE_10__* i2c; TYPE_9__* gpio; TYPE_8__* fuse; TYPE_7__* fb; TYPE_6__* fault; TYPE_5__* devinit; TYPE_4__* clk; TYPE_3__* bus; TYPE_2__* bios; TYPE_1__* bar; } ;
struct TYPE_44__ {struct nvkm_subdev subdev; } ;
struct TYPE_43__ {struct nvkm_subdev subdev; } ;
struct TYPE_42__ {struct nvkm_subdev subdev; } ;
struct TYPE_41__ {struct nvkm_subdev subdev; } ;
struct TYPE_40__ {struct nvkm_subdev subdev; } ;
struct TYPE_39__ {struct nvkm_subdev subdev; } ;
struct TYPE_38__ {struct nvkm_subdev subdev; } ;
struct TYPE_37__ {struct nvkm_subdev subdev; } ;
struct TYPE_36__ {struct nvkm_subdev subdev; } ;
struct TYPE_35__ {struct nvkm_subdev subdev; } ;
struct TYPE_34__ {struct nvkm_subdev subdev; } ;
struct TYPE_33__ {struct nvkm_subdev subdev; } ;
struct TYPE_32__ {struct nvkm_subdev subdev; } ;
struct TYPE_31__ {struct nvkm_subdev subdev; } ;
struct TYPE_30__ {struct nvkm_subdev subdev; } ;
struct TYPE_29__ {struct nvkm_subdev subdev; } ;
struct TYPE_28__ {struct nvkm_subdev subdev; } ;
struct TYPE_27__ {struct nvkm_subdev subdev; } ;
struct TYPE_26__ {struct nvkm_subdev subdev; } ;
struct TYPE_25__ {struct nvkm_subdev subdev; } ;
struct TYPE_24__ {struct nvkm_subdev subdev; } ;
struct TYPE_23__ {struct nvkm_subdev subdev; } ;

/* Variables and functions */
#define  NVKM_SUBDEV_BAR 151 
#define  NVKM_SUBDEV_BUS 150 
#define  NVKM_SUBDEV_CLK 149 
#define  NVKM_SUBDEV_DEVINIT 148 
#define  NVKM_SUBDEV_FAULT 147 
#define  NVKM_SUBDEV_FB 146 
#define  NVKM_SUBDEV_FUSE 145 
#define  NVKM_SUBDEV_GPIO 144 
#define  NVKM_SUBDEV_I2C 143 
#define  NVKM_SUBDEV_IBUS 142 
#define  NVKM_SUBDEV_ICCSENSE 141 
#define  NVKM_SUBDEV_INSTMEM 140 
#define  NVKM_SUBDEV_LTC 139 
#define  NVKM_SUBDEV_MC 138 
#define  NVKM_SUBDEV_MMU 137 
#define  NVKM_SUBDEV_MXM 136 
#define  NVKM_SUBDEV_PCI 135 
#define  NVKM_SUBDEV_PMU 134 
#define  NVKM_SUBDEV_SECBOOT 133 
#define  NVKM_SUBDEV_THERM 132 
#define  NVKM_SUBDEV_TIMER 131 
#define  NVKM_SUBDEV_TOP 130 
#define  NVKM_SUBDEV_VBIOS 129 
#define  NVKM_SUBDEV_VOLT 128 
 struct nvkm_engine* nvkm_device_engine (struct nvkm_device*,int) ; 

struct nvkm_subdev *
nvkm_device_subdev(struct nvkm_device *device, int index)
{
	struct nvkm_engine *engine;

	if (device->disable_mask & (1ULL << index))
		return NULL;

	switch (index) {
#define _(n,p,m) case NVKM_SUBDEV_##n: if (p) return (m); break
	_(BAR     , device->bar     , &device->bar->subdev);
	_(VBIOS   , device->bios    , &device->bios->subdev);
	_(BUS     , device->bus     , &device->bus->subdev);
	_(CLK     , device->clk     , &device->clk->subdev);
	_(DEVINIT , device->devinit , &device->devinit->subdev);
	_(FAULT   , device->fault   , &device->fault->subdev);
	_(FB      , device->fb      , &device->fb->subdev);
	_(FUSE    , device->fuse    , &device->fuse->subdev);
	_(GPIO    , device->gpio    , &device->gpio->subdev);
	_(I2C     , device->i2c     , &device->i2c->subdev);
	_(IBUS    , device->ibus    ,  device->ibus);
	_(ICCSENSE, device->iccsense, &device->iccsense->subdev);
	_(INSTMEM , device->imem    , &device->imem->subdev);
	_(LTC     , device->ltc     , &device->ltc->subdev);
	_(MC      , device->mc      , &device->mc->subdev);
	_(MMU     , device->mmu     , &device->mmu->subdev);
	_(MXM     , device->mxm     ,  device->mxm);
	_(PCI     , device->pci     , &device->pci->subdev);
	_(PMU     , device->pmu     , &device->pmu->subdev);
	_(SECBOOT , device->secboot , &device->secboot->subdev);
	_(THERM   , device->therm   , &device->therm->subdev);
	_(TIMER   , device->timer   , &device->timer->subdev);
	_(TOP     , device->top     , &device->top->subdev);
	_(VOLT    , device->volt    , &device->volt->subdev);
#undef _
	default:
		engine = nvkm_device_engine(device, index);
		if (engine)
			return &engine->subdev;
		break;
	}
	return NULL;
}