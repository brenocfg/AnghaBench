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
struct smp_resp {int result; } ;
typedef  struct smp_resp u8 ;
struct TYPE_2__ {scalar_t__ configuring; } ;
struct domain_device {int /*<<< orphan*/  sas_addr; TYPE_1__ ex_dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int HZ ; 
 int /*<<< orphan*/  RG_REQ_SIZE ; 
 int /*<<< orphan*/  RG_RESP_SIZE ; 
 int /*<<< orphan*/  SAS_ADDR (int /*<<< orphan*/ ) ; 
 struct smp_resp SMP_REPORT_GENERAL ; 
 int SMP_RESP_FUNC_ACC ; 
 struct smp_resp* alloc_smp_req (int /*<<< orphan*/ ) ; 
 struct smp_resp* alloc_smp_resp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ex_assign_report_general (struct domain_device*,struct smp_resp*) ; 
 int /*<<< orphan*/  kfree (struct smp_resp*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  pr_notice (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  schedule_timeout_interruptible (int) ; 
 int smp_execute_task (struct domain_device*,struct smp_resp*,int /*<<< orphan*/ ,struct smp_resp*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sas_ex_general(struct domain_device *dev)
{
	u8 *rg_req;
	struct smp_resp *rg_resp;
	int res;
	int i;

	rg_req = alloc_smp_req(RG_REQ_SIZE);
	if (!rg_req)
		return -ENOMEM;

	rg_resp = alloc_smp_resp(RG_RESP_SIZE);
	if (!rg_resp) {
		kfree(rg_req);
		return -ENOMEM;
	}

	rg_req[1] = SMP_REPORT_GENERAL;

	for (i = 0; i < 5; i++) {
		res = smp_execute_task(dev, rg_req, RG_REQ_SIZE, rg_resp,
				       RG_RESP_SIZE);

		if (res) {
			pr_notice("RG to ex %016llx failed:0x%x\n",
				  SAS_ADDR(dev->sas_addr), res);
			goto out;
		} else if (rg_resp->result != SMP_RESP_FUNC_ACC) {
			pr_debug("RG:ex %016llx returned SMP result:0x%x\n",
				 SAS_ADDR(dev->sas_addr), rg_resp->result);
			res = rg_resp->result;
			goto out;
		}

		ex_assign_report_general(dev, rg_resp);

		if (dev->ex_dev.configuring) {
			pr_debug("RG: ex %llx self-configuring...\n",
				 SAS_ADDR(dev->sas_addr));
			schedule_timeout_interruptible(5*HZ);
		} else
			break;
	}
out:
	kfree(rg_req);
	kfree(rg_resp);
	return res;
}