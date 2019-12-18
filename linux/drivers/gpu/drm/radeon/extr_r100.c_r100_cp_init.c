#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct radeon_ring {int align_mask; int gpu_addr; int wptr; int ready; scalar_t__ rptr_save_reg; } ;
struct TYPE_4__ {int /*<<< orphan*/  real_vram_size; } ;
struct TYPE_3__ {int gpu_addr; scalar_t__ enabled; } ;
struct radeon_device {TYPE_2__ mc; struct radeon_ring* ring; int /*<<< orphan*/  pdev; TYPE_1__ wb; int /*<<< orphan*/  me_fw; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int /*<<< orphan*/  DRM_INFO (char*,unsigned long) ; 
 int RADEON_BUF_SWAP_32BIT ; 
 int RADEON_CP_CSQ_CNTL ; 
 int RADEON_CP_CSQ_MODE ; 
 int /*<<< orphan*/  RADEON_CP_PACKET2 ; 
 int RADEON_CP_RB_BASE ; 
 int RADEON_CP_RB_CNTL ; 
 int RADEON_CP_RB_RPTR_WR ; 
 int RADEON_CP_RB_WPTR ; 
 int RADEON_CP_RB_WPTR_DELAY ; 
 int RADEON_CSQ_PRIBM_INDBM ; 
 int /*<<< orphan*/  RADEON_INDIRECT1_START ; 
 int /*<<< orphan*/  RADEON_INDIRECT2_START ; 
 int /*<<< orphan*/  RADEON_MAX_FETCH ; 
 int /*<<< orphan*/  RADEON_RB_BLKSZ ; 
 int /*<<< orphan*/  RADEON_RB_BUFSZ ; 
 int RADEON_RB_NO_UPDATE ; 
 int RADEON_RB_RPTR_WR_ENA ; 
 size_t RADEON_RING_TYPE_GFX_INDEX ; 
 int RADEON_WB_CP_RPTR_OFFSET ; 
 int RADEON_WB_SCRATCH_OFFSET ; 
 int REG_SET (int /*<<< orphan*/ ,unsigned int) ; 
 int R_00070C_CP_RB_RPTR_ADDR ; 
 int R_000770_SCRATCH_UMSK ; 
 int R_000774_SCRATCH_ADDR ; 
 int S_00070C_RB_RPTR_ADDR (int) ; 
 int /*<<< orphan*/  WREG32 (int,int) ; 
 unsigned int order_base_2 (unsigned int) ; 
 int /*<<< orphan*/  pci_set_master (int /*<<< orphan*/ ) ; 
 int r100_cp_init_microcode (struct radeon_device*) ; 
 int /*<<< orphan*/  r100_cp_load_microcode (struct radeon_device*) ; 
 scalar_t__ r100_debugfs_cp_init (struct radeon_device*) ; 
 int radeon_ring_init (struct radeon_device*,struct radeon_ring*,unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_ring_start (struct radeon_device*,size_t,struct radeon_ring*) ; 
 scalar_t__ radeon_ring_supports_scratch_reg (struct radeon_device*,struct radeon_ring*) ; 
 int radeon_ring_test (struct radeon_device*,size_t,struct radeon_ring*) ; 
 int radeon_scratch_get (struct radeon_device*,scalar_t__*) ; 
 int /*<<< orphan*/  radeon_ttm_set_active_vram_size (struct radeon_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

int r100_cp_init(struct radeon_device *rdev, unsigned ring_size)
{
	struct radeon_ring *ring = &rdev->ring[RADEON_RING_TYPE_GFX_INDEX];
	unsigned rb_bufsz;
	unsigned rb_blksz;
	unsigned max_fetch;
	unsigned pre_write_timer;
	unsigned pre_write_limit;
	unsigned indirect2_start;
	unsigned indirect1_start;
	uint32_t tmp;
	int r;

	if (r100_debugfs_cp_init(rdev)) {
		DRM_ERROR("Failed to register debugfs file for CP !\n");
	}
	if (!rdev->me_fw) {
		r = r100_cp_init_microcode(rdev);
		if (r) {
			DRM_ERROR("Failed to load firmware!\n");
			return r;
		}
	}

	/* Align ring size */
	rb_bufsz = order_base_2(ring_size / 8);
	ring_size = (1 << (rb_bufsz + 1)) * 4;
	r100_cp_load_microcode(rdev);
	r = radeon_ring_init(rdev, ring, ring_size, RADEON_WB_CP_RPTR_OFFSET,
			     RADEON_CP_PACKET2);
	if (r) {
		return r;
	}
	/* Each time the cp read 1024 bytes (16 dword/quadword) update
	 * the rptr copy in system ram */
	rb_blksz = 9;
	/* cp will read 128bytes at a time (4 dwords) */
	max_fetch = 1;
	ring->align_mask = 16 - 1;
	/* Write to CP_RB_WPTR will be delayed for pre_write_timer clocks */
	pre_write_timer = 64;
	/* Force CP_RB_WPTR write if written more than one time before the
	 * delay expire
	 */
	pre_write_limit = 0;
	/* Setup the cp cache like this (cache size is 96 dwords) :
	 *	RING		0  to 15
	 *	INDIRECT1	16 to 79
	 *	INDIRECT2	80 to 95
	 * So ring cache size is 16dwords (> (2 * max_fetch = 2 * 4dwords))
	 *    indirect1 cache size is 64dwords (> (2 * max_fetch = 2 * 4dwords))
	 *    indirect2 cache size is 16dwords (> (2 * max_fetch = 2 * 4dwords))
	 * Idea being that most of the gpu cmd will be through indirect1 buffer
	 * so it gets the bigger cache.
	 */
	indirect2_start = 80;
	indirect1_start = 16;
	/* cp setup */
	WREG32(0x718, pre_write_timer | (pre_write_limit << 28));
	tmp = (REG_SET(RADEON_RB_BUFSZ, rb_bufsz) |
	       REG_SET(RADEON_RB_BLKSZ, rb_blksz) |
	       REG_SET(RADEON_MAX_FETCH, max_fetch));
#ifdef __BIG_ENDIAN
	tmp |= RADEON_BUF_SWAP_32BIT;
#endif
	WREG32(RADEON_CP_RB_CNTL, tmp | RADEON_RB_NO_UPDATE);

	/* Set ring address */
	DRM_INFO("radeon: ring at 0x%016lX\n", (unsigned long)ring->gpu_addr);
	WREG32(RADEON_CP_RB_BASE, ring->gpu_addr);
	/* Force read & write ptr to 0 */
	WREG32(RADEON_CP_RB_CNTL, tmp | RADEON_RB_RPTR_WR_ENA | RADEON_RB_NO_UPDATE);
	WREG32(RADEON_CP_RB_RPTR_WR, 0);
	ring->wptr = 0;
	WREG32(RADEON_CP_RB_WPTR, ring->wptr);

	/* set the wb address whether it's enabled or not */
	WREG32(R_00070C_CP_RB_RPTR_ADDR,
		S_00070C_RB_RPTR_ADDR((rdev->wb.gpu_addr + RADEON_WB_CP_RPTR_OFFSET) >> 2));
	WREG32(R_000774_SCRATCH_ADDR, rdev->wb.gpu_addr + RADEON_WB_SCRATCH_OFFSET);

	if (rdev->wb.enabled)
		WREG32(R_000770_SCRATCH_UMSK, 0xff);
	else {
		tmp |= RADEON_RB_NO_UPDATE;
		WREG32(R_000770_SCRATCH_UMSK, 0);
	}

	WREG32(RADEON_CP_RB_CNTL, tmp);
	udelay(10);
	/* Set cp mode to bus mastering & enable cp*/
	WREG32(RADEON_CP_CSQ_MODE,
	       REG_SET(RADEON_INDIRECT2_START, indirect2_start) |
	       REG_SET(RADEON_INDIRECT1_START, indirect1_start));
	WREG32(RADEON_CP_RB_WPTR_DELAY, 0);
	WREG32(RADEON_CP_CSQ_MODE, 0x00004D4D);
	WREG32(RADEON_CP_CSQ_CNTL, RADEON_CSQ_PRIBM_INDBM);

	/* at this point everything should be setup correctly to enable master */
	pci_set_master(rdev->pdev);

	radeon_ring_start(rdev, RADEON_RING_TYPE_GFX_INDEX, &rdev->ring[RADEON_RING_TYPE_GFX_INDEX]);
	r = radeon_ring_test(rdev, RADEON_RING_TYPE_GFX_INDEX, ring);
	if (r) {
		DRM_ERROR("radeon: cp isn't working (%d).\n", r);
		return r;
	}
	ring->ready = true;
	radeon_ttm_set_active_vram_size(rdev, rdev->mc.real_vram_size);

	if (!ring->rptr_save_reg /* not resuming from suspend */
	    && radeon_ring_supports_scratch_reg(rdev, ring)) {
		r = radeon_scratch_get(rdev, &ring->rptr_save_reg);
		if (r) {
			DRM_ERROR("failed to get scratch reg for rptr save (%d).\n", r);
			ring->rptr_save_reg = 0;
		}
	}
	return 0;
}