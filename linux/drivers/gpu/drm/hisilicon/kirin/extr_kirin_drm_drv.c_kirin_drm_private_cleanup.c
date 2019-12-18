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
struct kirin_drm_private {int /*<<< orphan*/  hw_ctx; } ;
struct kirin_drm_data {int /*<<< orphan*/  (* cleanup_hw_ctx ) (int /*<<< orphan*/ ) ;} ;
struct drm_device {struct kirin_drm_private* dev_private; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ ,struct kirin_drm_private*) ; 
 scalar_t__ of_device_get_match_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kirin_drm_private_cleanup(struct drm_device *dev)
{
	struct kirin_drm_private *kirin_priv = dev->dev_private;
	struct kirin_drm_data *data;

	data = (struct kirin_drm_data *)of_device_get_match_data(dev->dev);
	if (data->cleanup_hw_ctx)
		data->cleanup_hw_ctx(kirin_priv->hw_ctx);

	devm_kfree(dev->dev, kirin_priv);
	dev->dev_private = NULL;
}