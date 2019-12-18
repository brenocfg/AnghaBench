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
struct bochs_device {struct drm_device* dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int bochs_hw_init (struct drm_device*) ; 
 int bochs_kms_init (struct bochs_device*) ; 
 int bochs_mm_init (struct bochs_device*) ; 
 int /*<<< orphan*/  bochs_unload (struct drm_device*) ; 
 struct bochs_device* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bochs_load(struct drm_device *dev)
{
	struct bochs_device *bochs;
	int ret;

	bochs = kzalloc(sizeof(*bochs), GFP_KERNEL);
	if (bochs == NULL)
		return -ENOMEM;
	dev->dev_private = bochs;
	bochs->dev = dev;

	ret = bochs_hw_init(dev);
	if (ret)
		goto err;

	ret = bochs_mm_init(bochs);
	if (ret)
		goto err;

	ret = bochs_kms_init(bochs);
	if (ret)
		goto err;

	return 0;

err:
	bochs_unload(dev);
	return ret;
}