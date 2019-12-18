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
typedef  int u32 ;
struct aac_dev {TYPE_1__** hba_map; } ;
struct aac_ciss_identify_pd {int dummy; } ;
struct TYPE_2__ {struct aac_ciss_identify_pd* safw_identify_resp; } ;

/* Variables and functions */
 int /*<<< orphan*/  aac_free_safw_all_identify_resp (struct aac_dev*,int) ; 
 int aac_get_safw_phys_bus (struct aac_dev*,int) ; 
 int aac_get_safw_phys_lun_count (struct aac_dev*) ; 
 int aac_get_safw_phys_target (struct aac_dev*,int) ; 
 int aac_issue_safw_bmic_identify (struct aac_dev*,struct aac_ciss_identify_pd**,int,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int aac_get_safw_attr_all_targets(struct aac_dev *dev)
{
	int i;
	int rcode = 0;
	u32 lun_count;
	u32 bus;
	u32 target;
	struct aac_ciss_identify_pd *identify_resp = NULL;

	lun_count = aac_get_safw_phys_lun_count(dev);

	for (i = 0; i < lun_count; ++i) {

		bus = aac_get_safw_phys_bus(dev, i);
		target = aac_get_safw_phys_target(dev, i);

		rcode = aac_issue_safw_bmic_identify(dev,
						&identify_resp, bus, target);

		if (unlikely(rcode < 0))
			goto free_identify_resp;

		dev->hba_map[bus][target].safw_identify_resp = identify_resp;
	}

out:
	return rcode;
free_identify_resp:
	aac_free_safw_all_identify_resp(dev, i);
	goto out;
}