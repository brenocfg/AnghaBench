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
struct reset_controller_dev {int dummy; } ;
struct qcom_aoss_reset_map {scalar_t__ reg; } ;
struct qcom_aoss_reset_data {scalar_t__ base; TYPE_1__* desc; } ;
struct TYPE_2__ {struct qcom_aoss_reset_map* resets; } ;

/* Variables and functions */
 struct qcom_aoss_reset_data* to_qcom_aoss_reset_data (struct reset_controller_dev*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int qcom_aoss_control_deassert(struct reset_controller_dev *rcdev,
				      unsigned long idx)
{
	struct qcom_aoss_reset_data *data = to_qcom_aoss_reset_data(rcdev);
	const struct qcom_aoss_reset_map *map = &data->desc->resets[idx];

	writel(0, data->base + map->reg);
	/* Wait 6 32kHz sleep cycles for reset */
	usleep_range(200, 300);
	return 0;
}