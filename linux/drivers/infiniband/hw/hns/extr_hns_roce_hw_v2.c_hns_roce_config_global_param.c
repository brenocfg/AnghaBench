#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct hns_roce_dev {int dummy; } ;
struct hns_roce_cmq_desc {scalar_t__ data; } ;
struct hns_roce_cfg_global_param {int /*<<< orphan*/  time_cfg_udp_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFG_GLOBAL_PARAM_DATA_0_ROCEE_TIME_1US_CFG_M ; 
 int /*<<< orphan*/  CFG_GLOBAL_PARAM_DATA_0_ROCEE_TIME_1US_CFG_S ; 
 int /*<<< orphan*/  CFG_GLOBAL_PARAM_DATA_0_ROCEE_UDP_PORT_M ; 
 int /*<<< orphan*/  CFG_GLOBAL_PARAM_DATA_0_ROCEE_UDP_PORT_S ; 
 int /*<<< orphan*/  HNS_ROCE_OPC_CFG_GLOBAL_PARAM ; 
 int hns_roce_cmq_send (struct hns_roce_dev*,struct hns_roce_cmq_desc*,int) ; 
 int /*<<< orphan*/  hns_roce_cmq_setup_basic_desc (struct hns_roce_cmq_desc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct hns_roce_cfg_global_param*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  roce_set_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hns_roce_config_global_param(struct hns_roce_dev *hr_dev)
{
	struct hns_roce_cfg_global_param *req;
	struct hns_roce_cmq_desc desc;

	hns_roce_cmq_setup_basic_desc(&desc, HNS_ROCE_OPC_CFG_GLOBAL_PARAM,
				      false);

	req = (struct hns_roce_cfg_global_param *)desc.data;
	memset(req, 0, sizeof(*req));
	roce_set_field(req->time_cfg_udp_port,
		       CFG_GLOBAL_PARAM_DATA_0_ROCEE_TIME_1US_CFG_M,
		       CFG_GLOBAL_PARAM_DATA_0_ROCEE_TIME_1US_CFG_S, 0x3e8);
	roce_set_field(req->time_cfg_udp_port,
		       CFG_GLOBAL_PARAM_DATA_0_ROCEE_UDP_PORT_M,
		       CFG_GLOBAL_PARAM_DATA_0_ROCEE_UDP_PORT_S, 0x12b7);

	return hns_roce_cmq_send(hr_dev, &desc, 1);
}