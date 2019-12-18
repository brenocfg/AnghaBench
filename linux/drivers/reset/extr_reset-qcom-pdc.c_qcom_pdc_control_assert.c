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
struct qcom_pdc_reset_data {int /*<<< orphan*/  regmap; } ;
struct TYPE_2__ {int /*<<< orphan*/  bit; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RPMH_PDC_SYNC_RESET ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* sdm845_pdc_resets ; 
 struct qcom_pdc_reset_data* to_qcom_pdc_reset_data (struct reset_controller_dev*) ; 

__attribute__((used)) static int qcom_pdc_control_assert(struct reset_controller_dev *rcdev,
					unsigned long idx)
{
	struct qcom_pdc_reset_data *data = to_qcom_pdc_reset_data(rcdev);

	return regmap_update_bits(data->regmap, RPMH_PDC_SYNC_RESET,
				  BIT(sdm845_pdc_resets[idx].bit),
				  BIT(sdm845_pdc_resets[idx].bit));
}