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
struct bnxt_re_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bnxt_re_ib_unreg (struct bnxt_re_dev*) ; 

__attribute__((used)) static void bnxt_re_shutdown(void *p)
{
	struct bnxt_re_dev *rdev = p;

	if (!rdev)
		return;

	bnxt_re_ib_unreg(rdev);
}