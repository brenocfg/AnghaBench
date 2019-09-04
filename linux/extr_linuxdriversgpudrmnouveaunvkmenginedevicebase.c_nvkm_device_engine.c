#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct nvkm_engine {int dummy; } ;
struct nvkm_device {unsigned long long disable_mask; struct nvkm_engine* vp; struct nvkm_engine* vic; TYPE_8__* sw; TYPE_7__* sec2; struct nvkm_engine* sec; TYPE_6__* pm; TYPE_5__* nvdec; struct nvkm_engine** nvenc; struct nvkm_engine* msvld; struct nvkm_engine* msppp; struct nvkm_engine* mspdec; struct nvkm_engine* msenc; struct nvkm_engine* mpeg; struct nvkm_engine* me; struct nvkm_engine* ifb; TYPE_4__* gr; TYPE_3__* fifo; TYPE_2__* dma; TYPE_1__* disp; struct nvkm_engine* cipher; struct nvkm_engine** ce; struct nvkm_engine* bsp; } ;
struct TYPE_16__ {struct nvkm_engine engine; } ;
struct TYPE_15__ {struct nvkm_engine engine; } ;
struct TYPE_14__ {struct nvkm_engine engine; } ;
struct TYPE_13__ {struct nvkm_engine engine; } ;
struct TYPE_12__ {struct nvkm_engine engine; } ;
struct TYPE_11__ {struct nvkm_engine engine; } ;
struct TYPE_10__ {struct nvkm_engine engine; } ;
struct TYPE_9__ {struct nvkm_engine engine; } ;

/* Variables and functions */
#define  NVKM_ENGINE_BSP 159 
#define  NVKM_ENGINE_CE0 158 
#define  NVKM_ENGINE_CE1 157 
#define  NVKM_ENGINE_CE2 156 
#define  NVKM_ENGINE_CE3 155 
#define  NVKM_ENGINE_CE4 154 
#define  NVKM_ENGINE_CE5 153 
#define  NVKM_ENGINE_CE6 152 
#define  NVKM_ENGINE_CE7 151 
#define  NVKM_ENGINE_CE8 150 
#define  NVKM_ENGINE_CIPHER 149 
#define  NVKM_ENGINE_DISP 148 
#define  NVKM_ENGINE_DMAOBJ 147 
#define  NVKM_ENGINE_FIFO 146 
#define  NVKM_ENGINE_GR 145 
#define  NVKM_ENGINE_IFB 144 
#define  NVKM_ENGINE_ME 143 
#define  NVKM_ENGINE_MPEG 142 
#define  NVKM_ENGINE_MSENC 141 
#define  NVKM_ENGINE_MSPDEC 140 
#define  NVKM_ENGINE_MSPPP 139 
#define  NVKM_ENGINE_MSVLD 138 
#define  NVKM_ENGINE_NVDEC 137 
#define  NVKM_ENGINE_NVENC0 136 
#define  NVKM_ENGINE_NVENC1 135 
#define  NVKM_ENGINE_NVENC2 134 
#define  NVKM_ENGINE_PM 133 
#define  NVKM_ENGINE_SEC 132 
#define  NVKM_ENGINE_SEC2 131 
#define  NVKM_ENGINE_SW 130 
#define  NVKM_ENGINE_VIC 129 
#define  NVKM_ENGINE_VP 128 
 int /*<<< orphan*/  WARN_ON (int) ; 

struct nvkm_engine *
nvkm_device_engine(struct nvkm_device *device, int index)
{
	if (device->disable_mask & (1ULL << index))
		return NULL;

	switch (index) {
#define _(n,p,m) case NVKM_ENGINE_##n: if (p) return (m); break
	_(BSP    , device->bsp     ,  device->bsp);
	_(CE0    , device->ce[0]   ,  device->ce[0]);
	_(CE1    , device->ce[1]   ,  device->ce[1]);
	_(CE2    , device->ce[2]   ,  device->ce[2]);
	_(CE3    , device->ce[3]   ,  device->ce[3]);
	_(CE4    , device->ce[4]   ,  device->ce[4]);
	_(CE5    , device->ce[5]   ,  device->ce[5]);
	_(CE6    , device->ce[6]   ,  device->ce[6]);
	_(CE7    , device->ce[7]   ,  device->ce[7]);
	_(CE8    , device->ce[8]   ,  device->ce[8]);
	_(CIPHER , device->cipher  ,  device->cipher);
	_(DISP   , device->disp    , &device->disp->engine);
	_(DMAOBJ , device->dma     , &device->dma->engine);
	_(FIFO   , device->fifo    , &device->fifo->engine);
	_(GR     , device->gr      , &device->gr->engine);
	_(IFB    , device->ifb     ,  device->ifb);
	_(ME     , device->me      ,  device->me);
	_(MPEG   , device->mpeg    ,  device->mpeg);
	_(MSENC  , device->msenc   ,  device->msenc);
	_(MSPDEC , device->mspdec  ,  device->mspdec);
	_(MSPPP  , device->msppp   ,  device->msppp);
	_(MSVLD  , device->msvld   ,  device->msvld);
	_(NVENC0 , device->nvenc[0],  device->nvenc[0]);
	_(NVENC1 , device->nvenc[1],  device->nvenc[1]);
	_(NVENC2 , device->nvenc[2],  device->nvenc[2]);
	_(NVDEC  , device->nvdec   , &device->nvdec->engine);
	_(PM     , device->pm      , &device->pm->engine);
	_(SEC    , device->sec     ,  device->sec);
	_(SEC2   , device->sec2    , &device->sec2->engine);
	_(SW     , device->sw      , &device->sw->engine);
	_(VIC    , device->vic     ,  device->vic);
	_(VP     , device->vp      ,  device->vp);
#undef _
	default:
		WARN_ON(1);
		break;
	}
	return NULL;
}