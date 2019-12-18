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
struct qcom_glink {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  qcom_glink_native_remove (struct qcom_glink*) ; 
 int /*<<< orphan*/  qcom_glink_native_unregister (struct qcom_glink*) ; 

void qcom_glink_smem_unregister(struct qcom_glink *glink)
{
	qcom_glink_native_remove(glink);
	qcom_glink_native_unregister(glink);
}