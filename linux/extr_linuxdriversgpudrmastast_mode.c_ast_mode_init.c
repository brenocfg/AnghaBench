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

/* Variables and functions */
 int /*<<< orphan*/  ast_connector_init (struct drm_device*) ; 
 int /*<<< orphan*/  ast_crtc_init (struct drm_device*) ; 
 int /*<<< orphan*/  ast_cursor_init (struct drm_device*) ; 
 int /*<<< orphan*/  ast_encoder_init (struct drm_device*) ; 

int ast_mode_init(struct drm_device *dev)
{
	ast_cursor_init(dev);
	ast_crtc_init(dev);
	ast_encoder_init(dev);
	ast_connector_init(dev);
	return 0;
}