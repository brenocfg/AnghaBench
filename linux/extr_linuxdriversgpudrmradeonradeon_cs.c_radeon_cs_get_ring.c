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
typedef  int u32 ;
struct radeon_cs_parser {void* ring; TYPE_1__* rdev; int /*<<< orphan*/  priority; } ;
typedef  int /*<<< orphan*/  s32 ;
struct TYPE_2__ {int /*<<< orphan*/  family; } ;

/* Variables and functions */
 void* CAYMAN_RING_TYPE_CP1_INDEX ; 
 void* CAYMAN_RING_TYPE_CP2_INDEX ; 
 void* CAYMAN_RING_TYPE_DMA1_INDEX ; 
 int /*<<< orphan*/  CHIP_CAYMAN ; 
 int /*<<< orphan*/  CHIP_RV770 ; 
 int /*<<< orphan*/  CHIP_TAHITI ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int EINVAL ; 
 void* R600_RING_TYPE_DMA_INDEX ; 
 void* R600_RING_TYPE_UVD_INDEX ; 
#define  RADEON_CS_RING_COMPUTE 132 
#define  RADEON_CS_RING_DMA 131 
#define  RADEON_CS_RING_GFX 130 
#define  RADEON_CS_RING_UVD 129 
#define  RADEON_CS_RING_VCE 128 
 void* RADEON_RING_TYPE_GFX_INDEX ; 
 void* TN_RING_TYPE_VCE1_INDEX ; 

__attribute__((used)) static int radeon_cs_get_ring(struct radeon_cs_parser *p, u32 ring, s32 priority)
{
	p->priority = priority;

	switch (ring) {
	default:
		DRM_ERROR("unknown ring id: %d\n", ring);
		return -EINVAL;
	case RADEON_CS_RING_GFX:
		p->ring = RADEON_RING_TYPE_GFX_INDEX;
		break;
	case RADEON_CS_RING_COMPUTE:
		if (p->rdev->family >= CHIP_TAHITI) {
			if (p->priority > 0)
				p->ring = CAYMAN_RING_TYPE_CP1_INDEX;
			else
				p->ring = CAYMAN_RING_TYPE_CP2_INDEX;
		} else
			p->ring = RADEON_RING_TYPE_GFX_INDEX;
		break;
	case RADEON_CS_RING_DMA:
		if (p->rdev->family >= CHIP_CAYMAN) {
			if (p->priority > 0)
				p->ring = R600_RING_TYPE_DMA_INDEX;
			else
				p->ring = CAYMAN_RING_TYPE_DMA1_INDEX;
		} else if (p->rdev->family >= CHIP_RV770) {
			p->ring = R600_RING_TYPE_DMA_INDEX;
		} else {
			return -EINVAL;
		}
		break;
	case RADEON_CS_RING_UVD:
		p->ring = R600_RING_TYPE_UVD_INDEX;
		break;
	case RADEON_CS_RING_VCE:
		/* TODO: only use the low priority ring for now */
		p->ring = TN_RING_TYPE_VCE1_INDEX;
		break;
	}
	return 0;
}