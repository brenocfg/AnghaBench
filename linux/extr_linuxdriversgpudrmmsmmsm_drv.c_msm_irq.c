#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct msm_kms {TYPE_1__* funcs; } ;
struct msm_drm_private {struct msm_kms* kms; } ;
struct drm_device {struct msm_drm_private* dev_private; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* irq ) (struct msm_kms*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  stub1 (struct msm_kms*) ; 

__attribute__((used)) static irqreturn_t msm_irq(int irq, void *arg)
{
	struct drm_device *dev = arg;
	struct msm_drm_private *priv = dev->dev_private;
	struct msm_kms *kms = priv->kms;
	BUG_ON(!kms);
	return kms->funcs->irq(kms);
}