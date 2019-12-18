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
struct radeon_device {unsigned int num_gb_pipes; scalar_t__ family; int num_z_pipes; TYPE_1__* pdev; } ;
struct TYPE_2__ {int device; } ;

/* Variables and functions */
 scalar_t__ CHIP_RV530 ; 
 int /*<<< orphan*/  DRM_INFO (char*,unsigned int,int) ; 
 unsigned int R300_DC_AUTOFLUSH_ENABLE ; 
 unsigned int R300_DC_DC_DISABLE_IGNORE_PE ; 
 int /*<<< orphan*/  R300_DST_PIPE_CONFIG ; 
 unsigned int R300_ENABLE_TILING ; 
 int R300_GA_DEADLOCK_CNTL ; 
 int /*<<< orphan*/  R300_GA_ENHANCE ; 
 int R300_GA_FASTSYNC_CNTL ; 
 int /*<<< orphan*/  R300_GB_TILE_CONFIG ; 
 unsigned int R300_PIPE_AUTO_CONFIG ; 
 int /*<<< orphan*/  R300_RB2D_DSTCACHE_MODE ; 
 unsigned int R300_TILE_SIZE_16 ; 
 int /*<<< orphan*/  R400_GB_PIPE_SELECT ; 
 int /*<<< orphan*/  R500_SU_REG_DEST ; 
 unsigned int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RV530_GB_PIPE_SELECT2 ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 scalar_t__ r100_gui_wait_for_idle (struct radeon_device*) ; 

void r420_pipes_init(struct radeon_device *rdev)
{
	unsigned tmp;
	unsigned gb_pipe_select;
	unsigned num_pipes;

	/* GA_ENHANCE workaround TCL deadlock issue */
	WREG32(R300_GA_ENHANCE, R300_GA_DEADLOCK_CNTL | R300_GA_FASTSYNC_CNTL |
	       (1 << 2) | (1 << 3));
	/* add idle wait as per freedesktop.org bug 24041 */
	if (r100_gui_wait_for_idle(rdev)) {
		pr_warn("Failed to wait GUI idle while programming pipes. Bad things might happen.\n");
	}
	/* get max number of pipes */
	gb_pipe_select = RREG32(R400_GB_PIPE_SELECT);
	num_pipes = ((gb_pipe_select >> 12) & 3) + 1;

	/* SE chips have 1 pipe */
	if ((rdev->pdev->device == 0x5e4c) ||
	    (rdev->pdev->device == 0x5e4f))
		num_pipes = 1;

	rdev->num_gb_pipes = num_pipes;
	tmp = 0;
	switch (num_pipes) {
	default:
		/* force to 1 pipe */
		num_pipes = 1;
		/* fall through */
	case 1:
		tmp = (0 << 1);
		break;
	case 2:
		tmp = (3 << 1);
		break;
	case 3:
		tmp = (6 << 1);
		break;
	case 4:
		tmp = (7 << 1);
		break;
	}
	WREG32(R500_SU_REG_DEST, (1 << num_pipes) - 1);
	/* Sub pixel 1/12 so we can have 4K rendering according to doc */
	tmp |= R300_TILE_SIZE_16 | R300_ENABLE_TILING;
	WREG32(R300_GB_TILE_CONFIG, tmp);
	if (r100_gui_wait_for_idle(rdev)) {
		pr_warn("Failed to wait GUI idle while programming pipes. Bad things might happen.\n");
	}

	tmp = RREG32(R300_DST_PIPE_CONFIG);
	WREG32(R300_DST_PIPE_CONFIG, tmp | R300_PIPE_AUTO_CONFIG);

	WREG32(R300_RB2D_DSTCACHE_MODE,
	       RREG32(R300_RB2D_DSTCACHE_MODE) |
	       R300_DC_AUTOFLUSH_ENABLE |
	       R300_DC_DC_DISABLE_IGNORE_PE);

	if (r100_gui_wait_for_idle(rdev)) {
		pr_warn("Failed to wait GUI idle while programming pipes. Bad things might happen.\n");
	}

	if (rdev->family == CHIP_RV530) {
		tmp = RREG32(RV530_GB_PIPE_SELECT2);
		if ((tmp & 3) == 3)
			rdev->num_z_pipes = 2;
		else
			rdev->num_z_pipes = 1;
	} else
		rdev->num_z_pipes = 1;

	DRM_INFO("radeon: %d quad pipes, %d z pipes initialized.\n",
		 rdev->num_gb_pipes, rdev->num_z_pipes);
}