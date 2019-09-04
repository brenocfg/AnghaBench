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
struct radeon_ring {int idx; int pipe; int /*<<< orphan*/  me; } ;
struct radeon_device {struct radeon_ring* ring; } ;

/* Variables and functions */
#define  CAYMAN_RING_TYPE_CP1_INDEX 130 
#define  CAYMAN_RING_TYPE_CP2_INDEX 129 
 int CP0 ; 
 int CP2 ; 
 int CP6 ; 
 int GPU_HDP_FLUSH_DONE ; 
 int GPU_HDP_FLUSH_REQ ; 
 int PACKET3 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PACKET3_WAIT_REG_MEM ; 
#define  RADEON_RING_TYPE_GFX_INDEX 128 
 int WAIT_REG_MEM_ENGINE (int) ; 
 int WAIT_REG_MEM_FUNCTION (int) ; 
 int WAIT_REG_MEM_OPERATION (int) ; 
 int /*<<< orphan*/  radeon_ring_write (struct radeon_ring*,int) ; 

__attribute__((used)) static void cik_hdp_flush_cp_ring_emit(struct radeon_device *rdev,
				       int ridx)
{
	struct radeon_ring *ring = &rdev->ring[ridx];
	u32 ref_and_mask;

	switch (ring->idx) {
	case CAYMAN_RING_TYPE_CP1_INDEX:
	case CAYMAN_RING_TYPE_CP2_INDEX:
	default:
		switch (ring->me) {
		case 0:
			ref_and_mask = CP2 << ring->pipe;
			break;
		case 1:
			ref_and_mask = CP6 << ring->pipe;
			break;
		default:
			return;
		}
		break;
	case RADEON_RING_TYPE_GFX_INDEX:
		ref_and_mask = CP0;
		break;
	}

	radeon_ring_write(ring, PACKET3(PACKET3_WAIT_REG_MEM, 5));
	radeon_ring_write(ring, (WAIT_REG_MEM_OPERATION(1) | /* write, wait, write */
				 WAIT_REG_MEM_FUNCTION(3) |  /* == */
				 WAIT_REG_MEM_ENGINE(1)));   /* pfp */
	radeon_ring_write(ring, GPU_HDP_FLUSH_REQ >> 2);
	radeon_ring_write(ring, GPU_HDP_FLUSH_DONE >> 2);
	radeon_ring_write(ring, ref_and_mask);
	radeon_ring_write(ring, ref_and_mask);
	radeon_ring_write(ring, 0x20); /* poll interval */
}