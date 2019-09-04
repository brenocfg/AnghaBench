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

/* Variables and functions */
 int /*<<< orphan*/  EXYNOS_CIICBSA (int) ; 
 int /*<<< orphan*/  EXYNOS_CIICRSA (int) ; 
 int /*<<< orphan*/  EXYNOS_CIIYSA (int) ; 
 int /*<<< orphan*/  EXYNOS_CIOCBSA (int) ; 
 int /*<<< orphan*/  EXYNOS_CIOCRSA (int) ; 
 int /*<<< orphan*/  EXYNOS_CIOYSA (int) ; 
 int FIMC_MAX_DST ; 
 int FIMC_MAX_SRC ; 
 int /*<<< orphan*/  fimc_write (struct fimc_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fimc_clear_addr(struct fimc_context *ctx)
{
	int i;

	for (i = 0; i < FIMC_MAX_SRC; i++) {
		fimc_write(ctx, 0, EXYNOS_CIIYSA(i));
		fimc_write(ctx, 0, EXYNOS_CIICBSA(i));
		fimc_write(ctx, 0, EXYNOS_CIICRSA(i));
	}

	for (i = 0; i < FIMC_MAX_DST; i++) {
		fimc_write(ctx, 0, EXYNOS_CIOYSA(i));
		fimc_write(ctx, 0, EXYNOS_CIOCBSA(i));
		fimc_write(ctx, 0, EXYNOS_CIOCRSA(i));
	}
}