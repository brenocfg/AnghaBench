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
struct v4l2_create_buffers {int /*<<< orphan*/  format; int /*<<< orphan*/  memory; int /*<<< orphan*/  count; int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_cont (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prt_names (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_memory_names ; 
 int /*<<< orphan*/  v4l_print_format (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void v4l_print_create_buffers(const void *arg, bool write_only)
{
	const struct v4l2_create_buffers *p = arg;

	pr_cont("index=%d, count=%d, memory=%s, ",
			p->index, p->count,
			prt_names(p->memory, v4l2_memory_names));
	v4l_print_format(&p->format, write_only);
}