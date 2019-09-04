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
struct exynos_drm_crtc {TYPE_1__* pipe_clk; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* enable ) (TYPE_1__*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_1__*,int) ; 

__attribute__((used)) static inline void exynos_drm_pipe_clk_enable(struct exynos_drm_crtc *crtc,
					      bool enable)
{
	if (crtc->pipe_clk)
		crtc->pipe_clk->enable(crtc->pipe_clk, enable);
}