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
struct TYPE_2__ {int /*<<< orphan*/ * adap; int /*<<< orphan*/  unregister_work; } ;
struct drm_dp_aux {TYPE_1__ cec; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cec_unregister_adapter (int /*<<< orphan*/ *) ; 

void drm_dp_cec_unregister_connector(struct drm_dp_aux *aux)
{
	if (!aux->cec.adap)
		return;
	cancel_delayed_work_sync(&aux->cec.unregister_work);
	cec_unregister_adapter(aux->cec.adap);
	aux->cec.adap = NULL;
}