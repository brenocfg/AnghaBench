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
struct amdgpu_device {int asic_type; } ;

/* Variables and functions */
#define  CHIP_HAINAN 132 
#define  CHIP_OLAND 131 
#define  CHIP_PITCAIRN 130 
#define  CHIP_TAHITI 129 
#define  CHIP_VERDE 128 
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int PA_SC_RASTER_CONFIG__PKR_MAP__SHIFT ; 
 int PA_SC_RASTER_CONFIG__PKR_YSEL__SHIFT ; 
 int PA_SC_RASTER_CONFIG__RB_XSEL2__SHIFT ; 
 int PA_SC_RASTER_CONFIG__RB_XSEL__SHIFT ; 
 int PA_SC_RASTER_CONFIG__RB_YSEL__SHIFT ; 
 int PA_SC_RASTER_CONFIG__SE_MAP__SHIFT ; 
 int PA_SC_RASTER_CONFIG__SE_XSEL__SHIFT ; 
 int PA_SC_RASTER_CONFIG__SE_YSEL__SHIFT ; 

__attribute__((used)) static void gfx_v6_0_raster_config(struct amdgpu_device *adev, u32 *rconf)
{
	switch (adev->asic_type) {
	case CHIP_TAHITI:
	case CHIP_PITCAIRN:
		*rconf |=
			   (2 << PA_SC_RASTER_CONFIG__RB_XSEL2__SHIFT) |
			   (1 << PA_SC_RASTER_CONFIG__RB_XSEL__SHIFT) |
			   (2 << PA_SC_RASTER_CONFIG__PKR_MAP__SHIFT) |
			   (1 << PA_SC_RASTER_CONFIG__PKR_YSEL__SHIFT) |
			   (2 << PA_SC_RASTER_CONFIG__SE_MAP__SHIFT) |
			   (2 << PA_SC_RASTER_CONFIG__SE_XSEL__SHIFT) |
			   (2 << PA_SC_RASTER_CONFIG__SE_YSEL__SHIFT);
		break;
	case CHIP_VERDE:
		*rconf |=
			   (1 << PA_SC_RASTER_CONFIG__RB_XSEL__SHIFT) |
			   (2 << PA_SC_RASTER_CONFIG__PKR_MAP__SHIFT) |
			   (1 << PA_SC_RASTER_CONFIG__PKR_YSEL__SHIFT);
		break;
	case CHIP_OLAND:
		*rconf |= (1 << PA_SC_RASTER_CONFIG__RB_YSEL__SHIFT);
		break;
	case CHIP_HAINAN:
		*rconf |= 0x0;
		break;
	default:
		DRM_ERROR("unknown asic: 0x%x\n", adev->asic_type);
		break;
	}
}