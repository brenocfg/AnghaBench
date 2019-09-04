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
struct v4l2_query_ext_ctrl {int /*<<< orphan*/ * dims; int /*<<< orphan*/  nr_of_dims; int /*<<< orphan*/  elems; int /*<<< orphan*/  elem_size; int /*<<< orphan*/  flags; int /*<<< orphan*/  default_value; int /*<<< orphan*/  step; int /*<<< orphan*/  maximum; int /*<<< orphan*/  minimum; int /*<<< orphan*/  name; int /*<<< orphan*/  type; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_cont (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void v4l_print_query_ext_ctrl(const void *arg, bool write_only)
{
	const struct v4l2_query_ext_ctrl *p = arg;

	pr_cont("id=0x%x, type=%d, name=%.*s, min/max=%lld/%lld, step=%lld, default=%lld, flags=0x%08x, elem_size=%u, elems=%u, nr_of_dims=%u, dims=%u,%u,%u,%u\n",
			p->id, p->type, (int)sizeof(p->name), p->name,
			p->minimum, p->maximum,
			p->step, p->default_value, p->flags,
			p->elem_size, p->elems, p->nr_of_dims,
			p->dims[0], p->dims[1], p->dims[2], p->dims[3]);
}