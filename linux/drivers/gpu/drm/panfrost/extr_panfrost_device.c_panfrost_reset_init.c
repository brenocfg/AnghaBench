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
struct panfrost_device {int /*<<< orphan*/  rstc; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  devm_reset_control_array_get (int /*<<< orphan*/ ,int,int) ; 
 int reset_control_deassert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int panfrost_reset_init(struct panfrost_device *pfdev)
{
	int err;

	pfdev->rstc = devm_reset_control_array_get(pfdev->dev, false, true);
	if (IS_ERR(pfdev->rstc)) {
		dev_err(pfdev->dev, "get reset failed %ld\n", PTR_ERR(pfdev->rstc));
		return PTR_ERR(pfdev->rstc);
	}

	err = reset_control_deassert(pfdev->rstc);
	if (err)
		return err;

	return 0;
}