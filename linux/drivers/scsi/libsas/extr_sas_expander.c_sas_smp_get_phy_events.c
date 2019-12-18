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
typedef  int /*<<< orphan*/  u8 ;
struct sas_rphy {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct sas_phy {void* phy_reset_problem_count; void* loss_of_dword_sync_count; void* running_disparity_error_count; void* invalid_dword_count; int /*<<< orphan*/  number; TYPE_1__ dev; } ;
struct domain_device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  RPEL_REQ_SIZE ; 
 int /*<<< orphan*/  RPEL_RESP_SIZE ; 
 int /*<<< orphan*/  SMP_REPORT_PHY_ERR_LOG ; 
 int /*<<< orphan*/ * alloc_smp_req (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * alloc_smp_resp (int /*<<< orphan*/ ) ; 
 struct sas_rphy* dev_to_rphy (int /*<<< orphan*/ ) ; 
 void* get_unaligned_be32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 struct domain_device* sas_find_dev_by_rphy (struct sas_rphy*) ; 
 int smp_execute_task (struct domain_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int sas_smp_get_phy_events(struct sas_phy *phy)
{
	int res;
	u8 *req;
	u8 *resp;
	struct sas_rphy *rphy = dev_to_rphy(phy->dev.parent);
	struct domain_device *dev = sas_find_dev_by_rphy(rphy);

	req = alloc_smp_req(RPEL_REQ_SIZE);
	if (!req)
		return -ENOMEM;

	resp = alloc_smp_resp(RPEL_RESP_SIZE);
	if (!resp) {
		kfree(req);
		return -ENOMEM;
	}

	req[1] = SMP_REPORT_PHY_ERR_LOG;
	req[9] = phy->number;

	res = smp_execute_task(dev, req, RPEL_REQ_SIZE,
			            resp, RPEL_RESP_SIZE);

	if (res)
		goto out;

	phy->invalid_dword_count = get_unaligned_be32(&resp[12]);
	phy->running_disparity_error_count = get_unaligned_be32(&resp[16]);
	phy->loss_of_dword_sync_count = get_unaligned_be32(&resp[20]);
	phy->phy_reset_problem_count = get_unaligned_be32(&resp[24]);

 out:
	kfree(req);
	kfree(resp);
	return res;

}