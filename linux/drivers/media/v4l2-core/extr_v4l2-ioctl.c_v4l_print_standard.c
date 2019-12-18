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
struct TYPE_2__ {int /*<<< orphan*/  denominator; int /*<<< orphan*/  numerator; } ;
struct v4l2_standard {int /*<<< orphan*/  framelines; TYPE_1__ frameperiod; int /*<<< orphan*/  name; scalar_t__ id; int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_cont (char*,int /*<<< orphan*/ ,unsigned long long,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void v4l_print_standard(const void *arg, bool write_only)
{
	const struct v4l2_standard *p = arg;

	pr_cont("index=%u, id=0x%Lx, name=%.*s, fps=%u/%u, framelines=%u\n",
		p->index,
		(unsigned long long)p->id, (int)sizeof(p->name), p->name,
		p->frameperiod.numerator,
		p->frameperiod.denominator,
		p->framelines);
}