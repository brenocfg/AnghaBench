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
struct drm_device {struct bochs_device* dev_private; } ;
struct drm_crtc {int dummy; } ;
struct bochs_device {struct drm_crtc crtc; } ;

/* Variables and functions */
 int /*<<< orphan*/  bochs_crtc_funcs ; 
 int /*<<< orphan*/  bochs_helper_funcs ; 
 int /*<<< orphan*/  drm_crtc_helper_add (struct drm_crtc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_crtc_init (struct drm_device*,struct drm_crtc*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bochs_crtc_init(struct drm_device *dev)
{
	struct bochs_device *bochs = dev->dev_private;
	struct drm_crtc *crtc = &bochs->crtc;

	drm_crtc_init(dev, crtc, &bochs_crtc_funcs);
	drm_crtc_helper_add(crtc, &bochs_helper_funcs);
}