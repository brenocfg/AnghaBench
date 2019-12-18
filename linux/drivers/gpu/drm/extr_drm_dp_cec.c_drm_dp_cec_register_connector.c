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
struct TYPE_2__ {int adap; char const* name; int /*<<< orphan*/  unregister_work; struct device* parent; } ;
struct drm_dp_aux {TYPE_1__ cec; int /*<<< orphan*/  transfer; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  drm_dp_cec_unregister_work ; 

void drm_dp_cec_register_connector(struct drm_dp_aux *aux, const char *name,
				   struct device *parent)
{
	WARN_ON(aux->cec.adap);
	if (WARN_ON(!aux->transfer))
		return;
	aux->cec.name = name;
	aux->cec.parent = parent;
	INIT_DELAYED_WORK(&aux->cec.unregister_work,
			  drm_dp_cec_unregister_work);
}