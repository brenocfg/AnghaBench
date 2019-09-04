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
typedef  int u32 ;
struct drm_plane_state {scalar_t__ color_encoding; } ;

/* Variables and functions */
 int CFG_CSC_RGB_COMPUTER ; 
 int CFG_CSC_YUV_CCIR601 ; 
 int CFG_CSC_YUV_CCIR709 ; 
 scalar_t__ DRM_COLOR_YCBCR_BT709 ; 

__attribute__((used)) static inline u32 armada_csc(struct drm_plane_state *state)
{
	/*
	 * The CFG_CSC_RGB_* settings control the output of the colour space
	 * converter, setting the range of output values it produces.  Since
	 * we will be blending with the full-range graphics, we need to
	 * produce full-range RGB output from the conversion.
	 */
	return CFG_CSC_RGB_COMPUTER |
	       (state->color_encoding == DRM_COLOR_YCBCR_BT709 ?
			CFG_CSC_YUV_CCIR709 : CFG_CSC_YUV_CCIR601);
}