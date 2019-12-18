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
struct TYPE_2__ {int* pri_latency; size_t max_level; } ;
struct drm_i915_private {TYPE_1__ wm; } ;

/* Variables and functions */
 size_t G4X_WM_LEVEL_HPLL ; 
 size_t G4X_WM_LEVEL_NORMAL ; 
 size_t G4X_WM_LEVEL_SR ; 

__attribute__((used)) static void g4x_setup_wm_latency(struct drm_i915_private *dev_priv)
{
	/* all latencies in usec */
	dev_priv->wm.pri_latency[G4X_WM_LEVEL_NORMAL] = 5;
	dev_priv->wm.pri_latency[G4X_WM_LEVEL_SR] = 12;
	dev_priv->wm.pri_latency[G4X_WM_LEVEL_HPLL] = 35;

	dev_priv->wm.max_level = G4X_WM_LEVEL_HPLL;
}