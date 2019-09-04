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
struct mtk_drm_crtc {int ddp_comp_nr; int /*<<< orphan*/  mutex; TYPE_1__** ddp_comp; } ;
struct drm_crtc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_crtc_cleanup (struct drm_crtc*) ; 
 int /*<<< orphan*/  mtk_disp_mutex_put (int /*<<< orphan*/ ) ; 
 struct mtk_drm_crtc* to_mtk_crtc (struct drm_crtc*) ; 

__attribute__((used)) static void mtk_drm_crtc_destroy(struct drm_crtc *crtc)
{
	struct mtk_drm_crtc *mtk_crtc = to_mtk_crtc(crtc);
	int i;

	for (i = 0; i < mtk_crtc->ddp_comp_nr; i++)
		clk_unprepare(mtk_crtc->ddp_comp[i]->clk);

	mtk_disp_mutex_put(mtk_crtc->mutex);

	drm_crtc_cleanup(crtc);
}