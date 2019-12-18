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
struct reset_controller_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  qcom_aoss_control_assert (struct reset_controller_dev*,unsigned long) ; 
 int qcom_aoss_control_deassert (struct reset_controller_dev*,unsigned long) ; 

__attribute__((used)) static int qcom_aoss_control_reset(struct reset_controller_dev *rcdev,
					unsigned long idx)
{
	qcom_aoss_control_assert(rcdev, idx);

	return qcom_aoss_control_deassert(rcdev, idx);
}