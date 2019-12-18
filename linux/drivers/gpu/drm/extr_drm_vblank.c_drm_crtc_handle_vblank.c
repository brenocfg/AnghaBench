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
struct drm_crtc {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_crtc_index (struct drm_crtc*) ; 
 int drm_handle_vblank (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool drm_crtc_handle_vblank(struct drm_crtc *crtc)
{
	return drm_handle_vblank(crtc->dev, drm_crtc_index(crtc));
}