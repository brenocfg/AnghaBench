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
typedef  int u32 ;
struct drm_plane_state {int dummy; } ;
struct TYPE_2__ {int saturation; } ;

/* Variables and functions */
 TYPE_1__* drm_to_overlay_state (struct drm_plane_state*) ; 

__attribute__((used)) static inline u32 armada_spu_saturation(struct drm_plane_state *state)
{
	/* Docs say 15:0, but it seems to actually be 31:16 on Armada 510 */
	return drm_to_overlay_state(state)->saturation << 16;
}