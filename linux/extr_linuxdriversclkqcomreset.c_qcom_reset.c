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
struct reset_controller_dev {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* deassert ) (struct reset_controller_dev*,unsigned long) ;int /*<<< orphan*/  (* assert ) (struct reset_controller_dev*,unsigned long) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct reset_controller_dev*,unsigned long) ; 
 int /*<<< orphan*/  stub2 (struct reset_controller_dev*,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int qcom_reset(struct reset_controller_dev *rcdev, unsigned long id)
{
	rcdev->ops->assert(rcdev, id);
	udelay(1);
	rcdev->ops->deassert(rcdev, id);
	return 0;
}