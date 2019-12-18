#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct edid {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  lock; TYPE_2__* adap; int /*<<< orphan*/  parent; int /*<<< orphan*/  name; int /*<<< orphan*/  unregister_work; } ;
struct drm_dp_aux {TYPE_1__ cec; int /*<<< orphan*/  transfer; } ;
struct TYPE_9__ {int capabilities; unsigned int available_log_addrs; } ;

/* Variables and functions */
 int CEC_CAP_DEFAULTS ; 
 int CEC_CAP_MONITOR_ALL ; 
 int CEC_CAP_NEEDS_HPD ; 
 int CEC_CAP_RC ; 
 unsigned int CEC_MAX_LOG_ADDRS ; 
 int DP_CEC_MULTIPLE_LA_CAPABLE ; 
 int DP_CEC_SNOOPING_CAPABLE ; 
 scalar_t__ IS_ERR (TYPE_2__*) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 TYPE_2__* cec_allocate_adapter (int /*<<< orphan*/ *,struct drm_dp_aux*,int /*<<< orphan*/ ,int,unsigned int) ; 
 int /*<<< orphan*/  cec_delete_adapter (TYPE_2__*) ; 
 scalar_t__ cec_register_adapter (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cec_s_phys_addr_from_edid (TYPE_2__*,struct edid const*) ; 
 int /*<<< orphan*/  cec_unregister_adapter (TYPE_2__*) ; 
 int /*<<< orphan*/  drm_dp_cec_adap_ops ; 
 int /*<<< orphan*/  drm_dp_cec_cap (struct drm_dp_aux*,int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void drm_dp_cec_set_edid(struct drm_dp_aux *aux, const struct edid *edid)
{
	u32 cec_caps = CEC_CAP_DEFAULTS | CEC_CAP_NEEDS_HPD;
	unsigned int num_las = 1;
	u8 cap;

	/* No transfer function was set, so not a DP connector */
	if (!aux->transfer)
		return;

#ifndef CONFIG_MEDIA_CEC_RC
	/*
	 * CEC_CAP_RC is part of CEC_CAP_DEFAULTS, but it is stripped by
	 * cec_allocate_adapter() if CONFIG_MEDIA_CEC_RC is undefined.
	 *
	 * Do this here as well to ensure the tests against cec_caps are
	 * correct.
	 */
	cec_caps &= ~CEC_CAP_RC;
#endif
	cancel_delayed_work_sync(&aux->cec.unregister_work);

	mutex_lock(&aux->cec.lock);
	if (!drm_dp_cec_cap(aux, &cap)) {
		/* CEC is not supported, unregister any existing adapter */
		cec_unregister_adapter(aux->cec.adap);
		aux->cec.adap = NULL;
		goto unlock;
	}

	if (cap & DP_CEC_SNOOPING_CAPABLE)
		cec_caps |= CEC_CAP_MONITOR_ALL;
	if (cap & DP_CEC_MULTIPLE_LA_CAPABLE)
		num_las = CEC_MAX_LOG_ADDRS;

	if (aux->cec.adap) {
		if (aux->cec.adap->capabilities == cec_caps &&
		    aux->cec.adap->available_log_addrs == num_las) {
			/* Unchanged, so just set the phys addr */
			cec_s_phys_addr_from_edid(aux->cec.adap, edid);
			goto unlock;
		}
		/*
		 * The capabilities changed, so unregister the old
		 * adapter first.
		 */
		cec_unregister_adapter(aux->cec.adap);
	}

	/* Create a new adapter */
	aux->cec.adap = cec_allocate_adapter(&drm_dp_cec_adap_ops,
					     aux, aux->cec.name, cec_caps,
					     num_las);
	if (IS_ERR(aux->cec.adap)) {
		aux->cec.adap = NULL;
		goto unlock;
	}
	if (cec_register_adapter(aux->cec.adap, aux->cec.parent)) {
		cec_delete_adapter(aux->cec.adap);
		aux->cec.adap = NULL;
	} else {
		/*
		 * Update the phys addr for the new CEC adapter. When called
		 * from drm_dp_cec_register_connector() edid == NULL, so in
		 * that case the phys addr is just invalidated.
		 */
		cec_s_phys_addr_from_edid(aux->cec.adap, edid);
	}
unlock:
	mutex_unlock(&aux->cec.lock);
}