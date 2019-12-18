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

/* Variables and functions */
 int atmel_hlcdc_crtc_select_output_mode (struct drm_crtc_state*) ; 
 int atmel_hlcdc_plane_prepare_ahb_routing (struct drm_crtc_state*) ; 
 int atmel_hlcdc_plane_prepare_disc_area (struct drm_crtc_state*) ; 

__attribute__((used)) static int atmel_hlcdc_crtc_atomic_check(struct drm_crtc *c,
					 struct drm_crtc_state *s)
{
	int ret;

	ret = atmel_hlcdc_crtc_select_output_mode(s);
	if (ret)
		return ret;

	ret = atmel_hlcdc_plane_prepare_disc_area(s);
	if (ret)
		return ret;

	return atmel_hlcdc_plane_prepare_ahb_routing(s);
}