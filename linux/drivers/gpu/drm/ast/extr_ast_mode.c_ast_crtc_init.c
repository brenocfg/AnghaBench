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
struct drm_device {int dummy; } ;
struct ast_crtc {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ast_crtc_funcs ; 
 int /*<<< orphan*/  ast_crtc_helper_funcs ; 
 int /*<<< orphan*/  drm_crtc_helper_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_crtc_init (struct drm_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_mode_crtc_set_gamma_size (int /*<<< orphan*/ *,int) ; 
 struct ast_crtc* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ast_crtc_init(struct drm_device *dev)
{
	struct ast_crtc *crtc;

	crtc = kzalloc(sizeof(struct ast_crtc), GFP_KERNEL);
	if (!crtc)
		return -ENOMEM;

	drm_crtc_init(dev, &crtc->base, &ast_crtc_funcs);
	drm_mode_crtc_set_gamma_size(&crtc->base, 256);
	drm_crtc_helper_add(&crtc->base, &ast_crtc_helper_funcs);
	return 0;
}