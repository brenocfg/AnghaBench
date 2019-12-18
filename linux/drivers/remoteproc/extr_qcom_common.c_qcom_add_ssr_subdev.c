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
struct rproc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  unprepare; } ;
struct qcom_rproc_ssr {char const* name; TYPE_1__ subdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  rproc_add_subdev (struct rproc*,TYPE_1__*) ; 
 int /*<<< orphan*/  ssr_notify_unprepare ; 

void qcom_add_ssr_subdev(struct rproc *rproc, struct qcom_rproc_ssr *ssr,
			 const char *ssr_name)
{
	ssr->name = ssr_name;
	ssr->subdev.unprepare = ssr_notify_unprepare;

	rproc_add_subdev(rproc, &ssr->subdev);
}