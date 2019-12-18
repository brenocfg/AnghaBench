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
struct vmw_private {scalar_t__ active_display_unit; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_mode_config_cleanup (int /*<<< orphan*/ ) ; 
 scalar_t__ vmw_du_legacy ; 
 int vmw_kms_ldu_close_display (struct vmw_private*) ; 

int vmw_kms_close(struct vmw_private *dev_priv)
{
	int ret = 0;

	/*
	 * Docs says we should take the lock before calling this function
	 * but since it destroys encoders and our destructor calls
	 * drm_encoder_cleanup which takes the lock we deadlock.
	 */
	drm_mode_config_cleanup(dev_priv->dev);
	if (dev_priv->active_display_unit == vmw_du_legacy)
		ret = vmw_kms_ldu_close_display(dev_priv);

	return ret;
}