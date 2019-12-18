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
struct rpmsg_endpoint {int dummy; } ;
struct qcom_smd_endpoint {int /*<<< orphan*/  qsch; } ;

/* Variables and functions */
 int __qcom_smd_send (int /*<<< orphan*/ ,void*,int,int) ; 
 struct qcom_smd_endpoint* to_smd_endpoint (struct rpmsg_endpoint*) ; 

__attribute__((used)) static int qcom_smd_trysend(struct rpmsg_endpoint *ept, void *data, int len)
{
	struct qcom_smd_endpoint *qsept = to_smd_endpoint(ept);

	return __qcom_smd_send(qsept->qsch, data, len, false);
}