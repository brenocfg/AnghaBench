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
struct expander_device {int num_phys; TYPE_1__* ex_phy; } ;
struct domain_device {struct expander_device ex_dev; } ;
struct TYPE_2__ {int phy_change_count; } ;

/* Variables and functions */
#define  SMP_RESP_FUNC_ACC 130 
#define  SMP_RESP_NO_PHY 129 
#define  SMP_RESP_PHY_VACANT 128 
 int sas_get_phy_change_count (struct domain_device*,int,int*) ; 

__attribute__((used)) static int sas_find_bcast_phy(struct domain_device *dev, int *phy_id,
			      int from_phy, bool update)
{
	struct expander_device *ex = &dev->ex_dev;
	int res = 0;
	int i;

	for (i = from_phy; i < ex->num_phys; i++) {
		int phy_change_count = 0;

		res = sas_get_phy_change_count(dev, i, &phy_change_count);
		switch (res) {
		case SMP_RESP_PHY_VACANT:
		case SMP_RESP_NO_PHY:
			continue;
		case SMP_RESP_FUNC_ACC:
			break;
		default:
			return res;
		}

		if (phy_change_count != ex->ex_phy[i].phy_change_count) {
			if (update)
				ex->ex_phy[i].phy_change_count =
					phy_change_count;
			*phy_id = i;
			return 0;
		}
	}
	return 0;
}