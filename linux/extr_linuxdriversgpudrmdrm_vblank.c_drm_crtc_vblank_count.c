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
typedef  int /*<<< orphan*/  u64 ;
struct drm_crtc {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_crtc_index (struct drm_crtc*) ; 
 int /*<<< orphan*/  drm_vblank_count (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u64 drm_crtc_vblank_count(struct drm_crtc *crtc)
{
	return drm_vblank_count(crtc->dev, drm_crtc_index(crtc));
}