#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * cctx; } ;
struct TYPE_3__ {int /*<<< orphan*/ * res; } ;
struct bnxt_re_dev {TYPE_2__ qplib_res; TYPE_1__ rcfw; } ;

/* Variables and functions */

__attribute__((used)) static void bnxt_re_destroy_chip_ctx(struct bnxt_re_dev *rdev)
{
	rdev->rcfw.res = NULL;
	rdev->qplib_res.cctx = NULL;
}