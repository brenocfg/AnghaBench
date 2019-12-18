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
struct fimc_context {int dummy; } ;
struct exynos_drm_ipp_buffer {int /*<<< orphan*/ * dma_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXYNOS_CIOCBSA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXYNOS_CIOCRSA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXYNOS_CIOYSA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fimc_dst_set_buf_seq (struct fimc_context*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fimc_write (struct fimc_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fimc_dst_set_addr(struct fimc_context *ctx,
			     struct exynos_drm_ipp_buffer *buf)
{
	fimc_write(ctx, buf->dma_addr[0], EXYNOS_CIOYSA(0));
	fimc_write(ctx, buf->dma_addr[1], EXYNOS_CIOCBSA(0));
	fimc_write(ctx, buf->dma_addr[2], EXYNOS_CIOCRSA(0));

	fimc_dst_set_buf_seq(ctx, 0, true);
}