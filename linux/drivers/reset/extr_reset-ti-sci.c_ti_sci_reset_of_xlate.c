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
struct ti_sci_reset_data {int /*<<< orphan*/  idr; int /*<<< orphan*/  dev; } ;
struct ti_sci_reset_control {int /*<<< orphan*/  lock; int /*<<< orphan*/  reset_mask; int /*<<< orphan*/  dev_id; } ;
struct reset_controller_dev {scalar_t__ of_reset_n_cells; } ;
struct of_phandle_args {scalar_t__ args_count; int /*<<< orphan*/ * args; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ WARN_ON (int) ; 
 struct ti_sci_reset_control* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int idr_alloc (int /*<<< orphan*/ *,struct ti_sci_reset_control*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct ti_sci_reset_data* to_ti_sci_reset_data (struct reset_controller_dev*) ; 

__attribute__((used)) static int ti_sci_reset_of_xlate(struct reset_controller_dev *rcdev,
				 const struct of_phandle_args *reset_spec)
{
	struct ti_sci_reset_data *data = to_ti_sci_reset_data(rcdev);
	struct ti_sci_reset_control *control;

	if (WARN_ON(reset_spec->args_count != rcdev->of_reset_n_cells))
		return -EINVAL;

	control = devm_kzalloc(data->dev, sizeof(*control), GFP_KERNEL);
	if (!control)
		return -ENOMEM;

	control->dev_id = reset_spec->args[0];
	control->reset_mask = reset_spec->args[1];
	mutex_init(&control->lock);

	return idr_alloc(&data->idr, control, 0, 0, GFP_KERNEL);
}