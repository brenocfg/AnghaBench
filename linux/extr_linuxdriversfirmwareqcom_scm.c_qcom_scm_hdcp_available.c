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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  QCOM_SCM_CMD_HDCP ; 
 int /*<<< orphan*/  QCOM_SCM_SVC_HDCP ; 
 int __qcom_scm_is_call_available (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* __scm ; 
 int /*<<< orphan*/  qcom_scm_clk_disable () ; 
 int qcom_scm_clk_enable () ; 

bool qcom_scm_hdcp_available(void)
{
	int ret = qcom_scm_clk_enable();

	if (ret)
		return ret;

	ret = __qcom_scm_is_call_available(__scm->dev, QCOM_SCM_SVC_HDCP,
						QCOM_SCM_CMD_HDCP);

	qcom_scm_clk_disable();

	return ret > 0 ? true : false;
}