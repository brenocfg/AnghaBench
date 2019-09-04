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
 int dpu_crtc_is_enabled (struct drm_crtc*) ; 

__attribute__((used)) static bool _dpu_core_perf_crtc_is_power_on(struct drm_crtc *crtc)
{
	return dpu_crtc_is_enabled(crtc);
}