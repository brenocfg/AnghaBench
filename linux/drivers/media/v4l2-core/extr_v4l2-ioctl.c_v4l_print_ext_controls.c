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
struct v4l2_ext_controls {int count; TYPE_1__* controls; int /*<<< orphan*/  request_fd; int /*<<< orphan*/  error_idx; int /*<<< orphan*/  which; } ;
struct TYPE_2__ {int /*<<< orphan*/  size; int /*<<< orphan*/  id; int /*<<< orphan*/  value; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_cont (char*,...) ; 

__attribute__((used)) static void v4l_print_ext_controls(const void *arg, bool write_only)
{
	const struct v4l2_ext_controls *p = arg;
	int i;

	pr_cont("which=0x%x, count=%d, error_idx=%d, request_fd=%d",
			p->which, p->count, p->error_idx, p->request_fd);
	for (i = 0; i < p->count; i++) {
		if (!p->controls[i].size)
			pr_cont(", id/val=0x%x/0x%x",
				p->controls[i].id, p->controls[i].value);
		else
			pr_cont(", id/size=0x%x/%u",
				p->controls[i].id, p->controls[i].size);
	}
	pr_cont("\n");
}