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
struct v4l2_audioout {int /*<<< orphan*/  mode; int /*<<< orphan*/  capability; int /*<<< orphan*/  name; int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_cont (char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void v4l_print_audioout(const void *arg, bool write_only)
{
	const struct v4l2_audioout *p = arg;

	if (write_only)
		pr_cont("index=%u\n", p->index);
	else
		pr_cont("index=%u, name=%.*s, capability=0x%x, mode=0x%x\n",
			p->index, (int)sizeof(p->name), p->name,
			p->capability, p->mode);
}