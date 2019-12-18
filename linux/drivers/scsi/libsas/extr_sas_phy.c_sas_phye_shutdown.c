#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct work_struct {int dummy; } ;
struct sas_internal {TYPE_3__* dft; } ;
struct TYPE_5__ {TYPE_1__* shost; } ;
struct sas_ha_struct {TYPE_2__ core; } ;
struct asd_sas_phy {scalar_t__ in_shutdown; int /*<<< orphan*/  id; scalar_t__ enabled; scalar_t__ error; struct sas_ha_struct* ha; } ;
struct asd_sas_event {struct asd_sas_phy* phy; } ;
struct TYPE_6__ {int (* lldd_control_phy ) (struct asd_sas_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  transportt; } ;

/* Variables and functions */
 int /*<<< orphan*/  PHY_FUNC_DISABLE ; 
 int /*<<< orphan*/  pr_notice (char*,int /*<<< orphan*/ ,...) ; 
 int stub1 (struct asd_sas_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct asd_sas_event* to_asd_sas_event (struct work_struct*) ; 
 struct sas_internal* to_sas_internal (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sas_phye_shutdown(struct work_struct *work)
{
	struct asd_sas_event *ev = to_asd_sas_event(work);
	struct asd_sas_phy *phy = ev->phy;
	struct sas_ha_struct *sas_ha = phy->ha;
	struct sas_internal *i =
		to_sas_internal(sas_ha->core.shost->transportt);

	if (phy->enabled) {
		int ret;

		phy->error = 0;
		phy->enabled = 0;
		ret = i->dft->lldd_control_phy(phy, PHY_FUNC_DISABLE, NULL);
		if (ret)
			pr_notice("lldd disable phy%d returned %d\n", phy->id,
				  ret);
	} else
		pr_notice("phy%d is not enabled, cannot shutdown\n", phy->id);
	phy->in_shutdown = 0;
}