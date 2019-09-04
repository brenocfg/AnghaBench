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
struct sti_private {struct drm_device* drm_dev; } ;
struct drm_device {int /*<<< orphan*/  dev; void* dev_private; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ ,struct drm_device*) ; 
 int /*<<< orphan*/  drm_kms_helper_poll_init (struct drm_device*) ; 
 int /*<<< orphan*/  drm_mode_config_init (struct drm_device*) ; 
 struct sti_private* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sti_mode_config_init (struct drm_device*) ; 

__attribute__((used)) static int sti_init(struct drm_device *ddev)
{
	struct sti_private *private;

	private = kzalloc(sizeof(*private), GFP_KERNEL);
	if (!private)
		return -ENOMEM;

	ddev->dev_private = (void *)private;
	dev_set_drvdata(ddev->dev, ddev);
	private->drm_dev = ddev;

	drm_mode_config_init(ddev);

	sti_mode_config_init(ddev);

	drm_kms_helper_poll_init(ddev);

	return 0;
}