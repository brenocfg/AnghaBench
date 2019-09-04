#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  denominator; int /*<<< orphan*/  numerator; } ;
struct TYPE_4__ {int /*<<< orphan*/  top; int /*<<< orphan*/  left; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_6__ {int /*<<< orphan*/  top; int /*<<< orphan*/  left; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct v4l2_cropcap {TYPE_2__ pixelaspect; TYPE_1__ defrect; TYPE_3__ bounds; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_cont (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prt_names (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_type_names ; 

__attribute__((used)) static void v4l_print_cropcap(const void *arg, bool write_only)
{
	const struct v4l2_cropcap *p = arg;

	pr_cont("type=%s, bounds wxh=%dx%d, x,y=%d,%d, defrect wxh=%dx%d, x,y=%d,%d, pixelaspect %d/%d\n",
		prt_names(p->type, v4l2_type_names),
		p->bounds.width, p->bounds.height,
		p->bounds.left, p->bounds.top,
		p->defrect.width, p->defrect.height,
		p->defrect.left, p->defrect.top,
		p->pixelaspect.numerator, p->pixelaspect.denominator);
}