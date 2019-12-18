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
struct TYPE_2__ {int /*<<< orphan*/  change_count; } ;
struct smp_resp {int result; TYPE_1__ rg; } ;
typedef  struct smp_resp u8 ;
struct domain_device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  RG_REQ_SIZE ; 
 int /*<<< orphan*/  RG_RESP_SIZE ; 
 struct smp_resp SMP_REPORT_GENERAL ; 
 int SMP_RESP_FUNC_ACC ; 
 struct smp_resp* alloc_smp_req (int /*<<< orphan*/ ) ; 
 struct smp_resp* alloc_smp_resp (int /*<<< orphan*/ ) ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct smp_resp*) ; 
 int smp_execute_task (struct domain_device*,struct smp_resp*,int /*<<< orphan*/ ,struct smp_resp*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sas_get_ex_change_count(struct domain_device *dev, int *ecc)
{
	int res;
	u8  *rg_req;
	struct smp_resp  *rg_resp;

	rg_req = alloc_smp_req(RG_REQ_SIZE);
	if (!rg_req)
		return -ENOMEM;

	rg_resp = alloc_smp_resp(RG_RESP_SIZE);
	if (!rg_resp) {
		kfree(rg_req);
		return -ENOMEM;
	}

	rg_req[1] = SMP_REPORT_GENERAL;

	res = smp_execute_task(dev, rg_req, RG_REQ_SIZE, rg_resp,
			       RG_RESP_SIZE);
	if (res)
		goto out;
	if (rg_resp->result != SMP_RESP_FUNC_ACC) {
		res = rg_resp->result;
		goto out;
	}

	*ecc = be16_to_cpu(rg_resp->rg.change_count);
out:
	kfree(rg_resp);
	kfree(rg_req);
	return res;
}