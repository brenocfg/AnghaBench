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
struct hns_roce_sccc_clr_done {scalar_t__ clr_done; } ;
struct hns_roce_sccc_clr {int /*<<< orphan*/  qpn; } ;
struct hns_roce_qp {int /*<<< orphan*/  qpn; } ;
struct TYPE_2__ {int /*<<< orphan*/  scc_mutex; } ;
struct hns_roce_dev {TYPE_1__ qp_table; int /*<<< orphan*/  dev; } ;
struct hns_roce_cmq_desc {scalar_t__ data; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int HNS_ROCE_CMQ_SCC_CLR_DONE_CNT ; 
 int /*<<< orphan*/  HNS_ROCE_OPC_CLR_SCCC ; 
 int /*<<< orphan*/  HNS_ROCE_OPC_QUERY_SCCC ; 
 int /*<<< orphan*/  HNS_ROCE_OPC_RESET_SCCC ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int hns_roce_cmq_send (struct hns_roce_dev*,struct hns_roce_cmq_desc*,int) ; 
 int /*<<< orphan*/  hns_roce_cmq_setup_basic_desc (struct hns_roce_cmq_desc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hns_roce_v2_qp_flow_control_init(struct hns_roce_dev *hr_dev,
						struct hns_roce_qp *hr_qp)
{
	struct hns_roce_sccc_clr_done *resp;
	struct hns_roce_sccc_clr *clr;
	struct hns_roce_cmq_desc desc;
	int ret, i;

	mutex_lock(&hr_dev->qp_table.scc_mutex);

	/* set scc ctx clear done flag */
	hns_roce_cmq_setup_basic_desc(&desc, HNS_ROCE_OPC_RESET_SCCC, false);
	ret =  hns_roce_cmq_send(hr_dev, &desc, 1);
	if (ret) {
		dev_err(hr_dev->dev, "Reset SCC ctx  failed(%d)\n", ret);
		goto out;
	}

	/* clear scc context */
	hns_roce_cmq_setup_basic_desc(&desc, HNS_ROCE_OPC_CLR_SCCC, false);
	clr = (struct hns_roce_sccc_clr *)desc.data;
	clr->qpn = cpu_to_le32(hr_qp->qpn);
	ret =  hns_roce_cmq_send(hr_dev, &desc, 1);
	if (ret) {
		dev_err(hr_dev->dev, "Clear SCC ctx failed(%d)\n", ret);
		goto out;
	}

	/* query scc context clear is done or not */
	resp = (struct hns_roce_sccc_clr_done *)desc.data;
	for (i = 0; i <= HNS_ROCE_CMQ_SCC_CLR_DONE_CNT; i++) {
		hns_roce_cmq_setup_basic_desc(&desc,
					      HNS_ROCE_OPC_QUERY_SCCC, true);
		ret = hns_roce_cmq_send(hr_dev, &desc, 1);
		if (ret) {
			dev_err(hr_dev->dev, "Query clr cmq failed(%d)\n", ret);
			goto out;
		}

		if (resp->clr_done)
			goto out;

		msleep(20);
	}

	dev_err(hr_dev->dev, "Query SCC clr done flag overtime.\n");
	ret = -ETIMEDOUT;

out:
	mutex_unlock(&hr_dev->qp_table.scc_mutex);
	return ret;
}