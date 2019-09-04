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
struct sti_mixer {int /*<<< orphan*/  dev; } ;
struct sti_compositor {int dummy; } ;
struct drm_crtc {TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  primary; } ;

/* Variables and functions */
 struct sti_compositor* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 scalar_t__ drm_crtc_index (struct drm_crtc*) ; 
 int sti_compositor_debugfs_init (struct sti_compositor*,int /*<<< orphan*/ ) ; 
 struct sti_mixer* to_sti_mixer (struct drm_crtc*) ; 

__attribute__((used)) static int sti_crtc_late_register(struct drm_crtc *crtc)
{
	struct sti_mixer *mixer = to_sti_mixer(crtc);
	struct sti_compositor *compo = dev_get_drvdata(mixer->dev);

	if (drm_crtc_index(crtc) == 0)
		return sti_compositor_debugfs_init(compo, crtc->dev->primary);

	return 0;
}