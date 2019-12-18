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
struct drm_crtc_state {int dummy; } ;
struct drm_crtc {int dummy; } ;
struct arcpgu_drm_private {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int ARCPGU_CTRL_ENABLE_MASK ; 
 int /*<<< orphan*/  ARCPGU_REG_CTRL ; 
 int arc_pgu_read (struct arcpgu_drm_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arc_pgu_write (struct arcpgu_drm_private*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 
 struct arcpgu_drm_private* crtc_to_arcpgu_priv (struct drm_crtc*) ; 

__attribute__((used)) static void arc_pgu_crtc_atomic_enable(struct drm_crtc *crtc,
				       struct drm_crtc_state *old_state)
{
	struct arcpgu_drm_private *arcpgu = crtc_to_arcpgu_priv(crtc);

	clk_prepare_enable(arcpgu->clk);
	arc_pgu_write(arcpgu, ARCPGU_REG_CTRL,
		      arc_pgu_read(arcpgu, ARCPGU_REG_CTRL) |
		      ARCPGU_CTRL_ENABLE_MASK);
}