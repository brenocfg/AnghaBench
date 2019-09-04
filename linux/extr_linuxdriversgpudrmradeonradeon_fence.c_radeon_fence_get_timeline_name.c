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
struct radeon_fence {int ring; } ;
struct dma_fence {int dummy; } ;

/* Variables and functions */
#define  CAYMAN_RING_TYPE_CP1_INDEX 135 
#define  CAYMAN_RING_TYPE_CP2_INDEX 134 
#define  CAYMAN_RING_TYPE_DMA1_INDEX 133 
#define  R600_RING_TYPE_DMA_INDEX 132 
#define  R600_RING_TYPE_UVD_INDEX 131 
#define  RADEON_RING_TYPE_GFX_INDEX 130 
#define  TN_RING_TYPE_VCE1_INDEX 129 
#define  TN_RING_TYPE_VCE2_INDEX 128 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 struct radeon_fence* to_radeon_fence (struct dma_fence*) ; 

__attribute__((used)) static const char *radeon_fence_get_timeline_name(struct dma_fence *f)
{
	struct radeon_fence *fence = to_radeon_fence(f);
	switch (fence->ring) {
	case RADEON_RING_TYPE_GFX_INDEX: return "radeon.gfx";
	case CAYMAN_RING_TYPE_CP1_INDEX: return "radeon.cp1";
	case CAYMAN_RING_TYPE_CP2_INDEX: return "radeon.cp2";
	case R600_RING_TYPE_DMA_INDEX: return "radeon.dma";
	case CAYMAN_RING_TYPE_DMA1_INDEX: return "radeon.dma1";
	case R600_RING_TYPE_UVD_INDEX: return "radeon.uvd";
	case TN_RING_TYPE_VCE1_INDEX: return "radeon.vce1";
	case TN_RING_TYPE_VCE2_INDEX: return "radeon.vce2";
	default: WARN_ON_ONCE(1); return "radeon.unk";
	}
}