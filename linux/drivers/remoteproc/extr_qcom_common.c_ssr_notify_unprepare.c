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
struct rproc_subdev {int dummy; } ;
struct qcom_rproc_ssr {scalar_t__ name; } ;

/* Variables and functions */
 int /*<<< orphan*/  blocking_notifier_call_chain (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  ssr_notifiers ; 
 struct qcom_rproc_ssr* to_ssr_subdev (struct rproc_subdev*) ; 

__attribute__((used)) static void ssr_notify_unprepare(struct rproc_subdev *subdev)
{
	struct qcom_rproc_ssr *ssr = to_ssr_subdev(subdev);

	blocking_notifier_call_chain(&ssr_notifiers, 0, (void *)ssr->name);
}