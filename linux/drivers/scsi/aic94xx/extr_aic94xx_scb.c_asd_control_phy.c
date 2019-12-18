#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sas_phy_linkrates {int /*<<< orphan*/  maximum_linkrate; int /*<<< orphan*/  minimum_linkrate; } ;
struct asd_sas_phy {size_t id; TYPE_1__* ha; } ;
struct asd_phy_desc {int /*<<< orphan*/  max_sata_lrate; int /*<<< orphan*/  max_sas_lrate; int /*<<< orphan*/  min_sata_lrate; int /*<<< orphan*/  min_sas_lrate; } ;
struct asd_ha_struct {TYPE_2__* phys; } ;
struct asd_ascb {int dummy; } ;
typedef  enum phy_func { ____Placeholder_phy_func } phy_func ;
struct TYPE_4__ {struct asd_phy_desc* phy_desc; } ;
struct TYPE_3__ {struct asd_ha_struct* lldd_ha; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENOSYS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  PHY_FUNC_CLEAR_ERROR_LOG 130 
#define  PHY_FUNC_GET_EVENTS 129 
 int PHY_FUNC_LINK_RESET ; 
#define  PHY_FUNC_SET_LINK_RATE 128 
 struct asd_ascb* asd_ascb_alloc_list (struct asd_ha_struct*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asd_ascb_free (struct asd_ascb*) ; 
 int /*<<< orphan*/  asd_build_control_phy (struct asd_ascb*,size_t,int /*<<< orphan*/ ) ; 
 int asd_post_ascb_list (struct asd_ha_struct*,struct asd_ascb*,int) ; 
 int /*<<< orphan*/ * phy_func_table ; 

int asd_control_phy(struct asd_sas_phy *phy, enum phy_func func, void *arg)
{
	struct asd_ha_struct *asd_ha = phy->ha->lldd_ha;
	struct asd_phy_desc *pd = asd_ha->phys[phy->id].phy_desc;
	struct asd_ascb *ascb;
	struct sas_phy_linkrates *rates;
	int res = 1;

	switch (func) {
	case PHY_FUNC_CLEAR_ERROR_LOG:
	case PHY_FUNC_GET_EVENTS:
		return -ENOSYS;
	case PHY_FUNC_SET_LINK_RATE:
		rates = arg;
		if (rates->minimum_linkrate) {
			pd->min_sas_lrate = rates->minimum_linkrate;
			pd->min_sata_lrate = rates->minimum_linkrate;
		}
		if (rates->maximum_linkrate) {
			pd->max_sas_lrate = rates->maximum_linkrate;
			pd->max_sata_lrate = rates->maximum_linkrate;
		}
		func = PHY_FUNC_LINK_RESET;
		break;
	default:
		break;
	}

	ascb = asd_ascb_alloc_list(asd_ha, &res, GFP_KERNEL);
	if (!ascb)
		return -ENOMEM;

	asd_build_control_phy(ascb, phy->id, phy_func_table[func]);
	res = asd_post_ascb_list(asd_ha, ascb , 1);
	if (res)
		asd_ascb_free(ascb);

	return res;
}