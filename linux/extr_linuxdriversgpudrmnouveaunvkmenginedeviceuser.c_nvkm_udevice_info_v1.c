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
struct nvkm_device {int dummy; } ;
struct nv_device_info_v1_data {int mthd; unsigned long long data; } ;

/* Variables and functions */
 unsigned long long BIT_ULL (int) ; 
 int NVKM_ENGINE_BSP ; 
 int NVKM_ENGINE_CE0 ; 
 int NVKM_ENGINE_CE_LAST ; 
 int NVKM_ENGINE_CIPHER ; 
 int NVKM_ENGINE_GR ; 
 int NVKM_ENGINE_ME ; 
 int NVKM_ENGINE_MPEG ; 
 int NVKM_ENGINE_MSENC ; 
 int NVKM_ENGINE_MSPDEC ; 
 int NVKM_ENGINE_MSPPP ; 
 int NVKM_ENGINE_MSVLD ; 
 int NVKM_ENGINE_NVDEC ; 
 int NVKM_ENGINE_NVENC0 ; 
 int NVKM_ENGINE_NVENC_LAST ; 
 int NVKM_ENGINE_SEC ; 
 int NVKM_ENGINE_SEC2 ; 
 int NVKM_ENGINE_SW ; 
 int NVKM_ENGINE_VIC ; 
 int NVKM_ENGINE_VP ; 
#define  NV_DEVICE_INFO_ENGINE_BSP 144 
#define  NV_DEVICE_INFO_ENGINE_CE 143 
#define  NV_DEVICE_INFO_ENGINE_CIPHER 142 
#define  NV_DEVICE_INFO_ENGINE_GR 141 
#define  NV_DEVICE_INFO_ENGINE_ME 140 
#define  NV_DEVICE_INFO_ENGINE_MPEG 139 
#define  NV_DEVICE_INFO_ENGINE_MSENC 138 
#define  NV_DEVICE_INFO_ENGINE_MSPDEC 137 
#define  NV_DEVICE_INFO_ENGINE_MSPPP 136 
#define  NV_DEVICE_INFO_ENGINE_MSVLD 135 
#define  NV_DEVICE_INFO_ENGINE_NVDEC 134 
#define  NV_DEVICE_INFO_ENGINE_NVENC 133 
#define  NV_DEVICE_INFO_ENGINE_SEC 132 
#define  NV_DEVICE_INFO_ENGINE_SEC2 131 
#define  NV_DEVICE_INFO_ENGINE_SW 130 
#define  NV_DEVICE_INFO_ENGINE_VIC 129 
#define  NV_DEVICE_INFO_ENGINE_VP 128 
 void* NV_DEVICE_INFO_INVALID ; 
 int NV_DEVICE_INFO_UNIT ; 
 int /*<<< orphan*/  nvkm_device_engine (struct nvkm_device*,int) ; 
 scalar_t__ nvkm_udevice_info_subdev (struct nvkm_device*,int,unsigned long long*) ; 

__attribute__((used)) static void
nvkm_udevice_info_v1(struct nvkm_device *device,
		     struct nv_device_info_v1_data *args)
{
	if (args->mthd & NV_DEVICE_INFO_UNIT) {
		if (nvkm_udevice_info_subdev(device, args->mthd, &args->data))
			args->mthd = NV_DEVICE_INFO_INVALID;
		return;
	}

	switch (args->mthd) {
#define ENGINE__(A,B,C) NV_DEVICE_INFO_ENGINE_##A: { int _i;                   \
	for (_i = (B), args->data = 0ULL; _i <= (C); _i++) {                   \
		if (nvkm_device_engine(device, _i))                            \
			args->data |= BIT_ULL(_i);                             \
	}                                                                      \
}
#define ENGINE_A(A) ENGINE__(A, NVKM_ENGINE_##A   , NVKM_ENGINE_##A)
#define ENGINE_B(A) ENGINE__(A, NVKM_ENGINE_##A##0, NVKM_ENGINE_##A##_LAST)
	case ENGINE_A(SW    ); break;
	case ENGINE_A(GR    ); break;
	case ENGINE_A(MPEG  ); break;
	case ENGINE_A(ME    ); break;
	case ENGINE_A(CIPHER); break;
	case ENGINE_A(BSP   ); break;
	case ENGINE_A(VP    ); break;
	case ENGINE_B(CE    ); break;
	case ENGINE_A(SEC   ); break;
	case ENGINE_A(MSVLD ); break;
	case ENGINE_A(MSPDEC); break;
	case ENGINE_A(MSPPP ); break;
	case ENGINE_A(MSENC ); break;
	case ENGINE_A(VIC   ); break;
	case ENGINE_A(SEC2  ); break;
	case ENGINE_A(NVDEC ); break;
	case ENGINE_B(NVENC ); break;
	default:
		args->mthd = NV_DEVICE_INFO_INVALID;
		break;
	}
}