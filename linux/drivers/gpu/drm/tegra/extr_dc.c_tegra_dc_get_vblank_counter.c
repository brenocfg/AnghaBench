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
typedef  int /*<<< orphan*/  u32 ;
struct tegra_dc {int /*<<< orphan*/  base; scalar_t__ syncpt; TYPE_1__* soc; } ;
struct drm_crtc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  has_nvdisplay; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_crtc_vblank_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  host1x_syncpt_read (scalar_t__) ; 
 struct tegra_dc* to_tegra_dc (struct drm_crtc*) ; 

__attribute__((used)) static u32 tegra_dc_get_vblank_counter(struct drm_crtc *crtc)
{
	struct tegra_dc *dc = to_tegra_dc(crtc);

	/* XXX vblank syncpoints don't work with nvdisplay yet */
	if (dc->syncpt && !dc->soc->has_nvdisplay)
		return host1x_syncpt_read(dc->syncpt);

	/* fallback to software emulated VBLANK counter */
	return (u32)drm_crtc_vblank_count(&dc->base);
}