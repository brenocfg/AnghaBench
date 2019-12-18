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
struct bnxt_re_dev {int /*<<< orphan*/  ibdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ib_unregister_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bnxt_re_unregister_ib(struct bnxt_re_dev *rdev)
{
	ib_unregister_device(&rdev->ibdev);
}