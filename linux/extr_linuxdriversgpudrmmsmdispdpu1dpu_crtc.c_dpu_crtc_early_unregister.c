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
struct drm_crtc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _dpu_crtc_destroy_debugfs (struct drm_crtc*) ; 

__attribute__((used)) static void dpu_crtc_early_unregister(struct drm_crtc *crtc)
{
	_dpu_crtc_destroy_debugfs(crtc);
}