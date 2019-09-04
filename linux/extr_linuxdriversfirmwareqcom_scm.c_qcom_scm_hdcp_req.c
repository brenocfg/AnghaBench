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
typedef  int /*<<< orphan*/  u32 ;
struct qcom_scm_hdcp_req {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int __qcom_scm_hdcp_req (int /*<<< orphan*/ ,struct qcom_scm_hdcp_req*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* __scm ; 
 int /*<<< orphan*/  qcom_scm_clk_disable () ; 
 int qcom_scm_clk_enable () ; 

int qcom_scm_hdcp_req(struct qcom_scm_hdcp_req *req, u32 req_cnt, u32 *resp)
{
	int ret = qcom_scm_clk_enable();

	if (ret)
		return ret;

	ret = __qcom_scm_hdcp_req(__scm->dev, req, req_cnt, resp);
	qcom_scm_clk_disable();
	return ret;
}