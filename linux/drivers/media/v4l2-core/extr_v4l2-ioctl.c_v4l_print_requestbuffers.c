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
struct v4l2_requestbuffers {int /*<<< orphan*/  memory; int /*<<< orphan*/  type; int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_cont (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prt_names (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_memory_names ; 
 int /*<<< orphan*/  v4l2_type_names ; 

__attribute__((used)) static void v4l_print_requestbuffers(const void *arg, bool write_only)
{
	const struct v4l2_requestbuffers *p = arg;

	pr_cont("count=%d, type=%s, memory=%s\n",
		p->count,
		prt_names(p->type, v4l2_type_names),
		prt_names(p->memory, v4l2_memory_names));
}