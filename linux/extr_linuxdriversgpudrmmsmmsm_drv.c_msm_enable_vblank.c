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
struct msm_kms {int dummy; } ;
struct msm_drm_private {struct msm_kms* kms; } ;
struct drm_device {struct msm_drm_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,struct drm_device*,unsigned int) ; 
 int ENXIO ; 
 int vblank_ctrl_queue_work (struct msm_drm_private*,unsigned int,int) ; 

__attribute__((used)) static int msm_enable_vblank(struct drm_device *dev, unsigned int pipe)
{
	struct msm_drm_private *priv = dev->dev_private;
	struct msm_kms *kms = priv->kms;
	if (!kms)
		return -ENXIO;
	DBG("dev=%p, crtc=%u", dev, pipe);
	return vblank_ctrl_queue_work(priv, pipe, true);
}