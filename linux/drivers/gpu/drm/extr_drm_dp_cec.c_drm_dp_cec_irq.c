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
typedef  int u8 ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  adap; } ;
struct drm_dp_aux {TYPE_1__ cec; int /*<<< orphan*/  transfer; } ;

/* Variables and functions */
 int DP_CEC_IRQ ; 
 int /*<<< orphan*/  DP_DEVICE_SERVICE_IRQ_VECTOR_ESI1 ; 
 int /*<<< orphan*/  drm_dp_cec_handle_irq (struct drm_dp_aux*) ; 
 int drm_dp_dpcd_readb (struct drm_dp_aux*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  drm_dp_dpcd_writeb (struct drm_dp_aux*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void drm_dp_cec_irq(struct drm_dp_aux *aux)
{
	u8 cec_irq;
	int ret;

	/* No transfer function was set, so not a DP connector */
	if (!aux->transfer)
		return;

	mutex_lock(&aux->cec.lock);
	if (!aux->cec.adap)
		goto unlock;

	ret = drm_dp_dpcd_readb(aux, DP_DEVICE_SERVICE_IRQ_VECTOR_ESI1,
				&cec_irq);
	if (ret < 0 || !(cec_irq & DP_CEC_IRQ))
		goto unlock;

	drm_dp_cec_handle_irq(aux);
	drm_dp_dpcd_writeb(aux, DP_DEVICE_SERVICE_IRQ_VECTOR_ESI1, DP_CEC_IRQ);
unlock:
	mutex_unlock(&aux->cec.lock);
}