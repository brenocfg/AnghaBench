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
struct v4l2_fmtdesc {int pixelformat; int /*<<< orphan*/  description; int /*<<< orphan*/  flags; int /*<<< orphan*/  type; int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_cont (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prt_names (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_type_names ; 

__attribute__((used)) static void v4l_print_fmtdesc(const void *arg, bool write_only)
{
	const struct v4l2_fmtdesc *p = arg;

	pr_cont("index=%u, type=%s, flags=0x%x, pixelformat=%c%c%c%c, description='%.*s'\n",
		p->index, prt_names(p->type, v4l2_type_names),
		p->flags, (p->pixelformat & 0xff),
		(p->pixelformat >>  8) & 0xff,
		(p->pixelformat >> 16) & 0xff,
		(p->pixelformat >> 24) & 0xff,
		(int)sizeof(p->description), p->description);
}