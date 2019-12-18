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
typedef  int /*<<< orphan*/  u32 ;
struct fimc_context {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_DEBUG_KMS (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*) ; 
 int EIO ; 
 int /*<<< orphan*/  EXYNOS_CISTATUS2 ; 
 int EXYNOS_CISTATUS2_GET_FRAMECOUNT_BEFORE (int /*<<< orphan*/ ) ; 
 int EXYNOS_CISTATUS2_GET_FRAMECOUNT_PRESENT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fimc_read (struct fimc_context*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fimc_get_buf_id(struct fimc_context *ctx)
{
	u32 cfg;
	int frame_cnt, buf_id;

	cfg = fimc_read(ctx, EXYNOS_CISTATUS2);
	frame_cnt = EXYNOS_CISTATUS2_GET_FRAMECOUNT_BEFORE(cfg);

	if (frame_cnt == 0)
		frame_cnt = EXYNOS_CISTATUS2_GET_FRAMECOUNT_PRESENT(cfg);

	DRM_DEV_DEBUG_KMS(ctx->dev, "present[%d]before[%d]\n",
			  EXYNOS_CISTATUS2_GET_FRAMECOUNT_PRESENT(cfg),
			  EXYNOS_CISTATUS2_GET_FRAMECOUNT_BEFORE(cfg));

	if (frame_cnt == 0) {
		DRM_DEV_ERROR(ctx->dev, "failed to get frame count.\n");
		return -EIO;
	}

	buf_id = frame_cnt - 1;
	DRM_DEV_DEBUG_KMS(ctx->dev, "buf_id[%d]\n", buf_id);

	return buf_id;
}