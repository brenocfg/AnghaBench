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
struct atmel_hlcdc_crtc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_crtc_cleanup (struct drm_crtc*) ; 
 struct atmel_hlcdc_crtc* drm_crtc_to_atmel_hlcdc_crtc (struct drm_crtc*) ; 
 int /*<<< orphan*/  kfree (struct atmel_hlcdc_crtc*) ; 

__attribute__((used)) static void atmel_hlcdc_crtc_destroy(struct drm_crtc *c)
{
	struct atmel_hlcdc_crtc *crtc = drm_crtc_to_atmel_hlcdc_crtc(c);

	drm_crtc_cleanup(c);
	kfree(crtc);
}