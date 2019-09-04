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
typedef  scalar_t__ u16 ;
struct hclge_vport {unsigned long* mta_shadow; int accept_mta_mc; int /*<<< orphan*/  vport_id; struct hclge_dev* back; } ;
struct hclge_dev {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ HCLGE_MTA_TBL_SIZE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int hclge_cfg_func_mta_filter (struct hclge_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hclge_set_mta_table_item (struct hclge_vport*,scalar_t__,int) ; 
 scalar_t__ test_bit (scalar_t__,unsigned long*) ; 

int hclge_update_mta_status_common(struct hclge_vport *vport,
				   unsigned long *status,
				   u16 idx,
				   u16 count,
				   bool update_filter)
{
	struct hclge_dev *hdev = vport->back;
	u16 update_max = idx + count;
	u16 check_max;
	int ret = 0;
	bool used;
	u16 i;

	/* setup mta check range */
	if (update_filter) {
		i = 0;
		check_max = HCLGE_MTA_TBL_SIZE;
	} else {
		i = idx;
		check_max = update_max;
	}

	used = false;
	/* check and update all mta item */
	for (; i < check_max; i++) {
		/* ignore unused item */
		if (!test_bit(i, vport->mta_shadow))
			continue;

		/* if i in update range then update it */
		if (i >= idx && i < update_max)
			if (!test_bit(i - idx, status))
				hclge_set_mta_table_item(vport, i, false);

		if (!used && test_bit(i, vport->mta_shadow))
			used = true;
	}

	/* no longer use mta, disable it */
	if (vport->accept_mta_mc && update_filter && !used) {
		ret = hclge_cfg_func_mta_filter(hdev,
						vport->vport_id,
						false);
		if (ret)
			dev_err(&hdev->pdev->dev,
				"disable func mta filter fail ret=%d\n",
				ret);
		else
			vport->accept_mta_mc = false;
	}

	return ret;
}