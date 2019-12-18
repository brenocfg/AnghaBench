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
struct qmi_service {struct qcom_sysmon* priv; } ;
struct qmi_handle {int dummy; } ;
struct qcom_sysmon {scalar_t__ ssctl_version; } ;

/* Variables and functions */

__attribute__((used)) static void ssctl_del_server(struct qmi_handle *qmi, struct qmi_service *svc)
{
	struct qcom_sysmon *sysmon = svc->priv;

	sysmon->ssctl_version = 0;
}