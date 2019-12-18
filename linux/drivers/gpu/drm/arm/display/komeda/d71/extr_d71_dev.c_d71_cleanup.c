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
struct komeda_dev {struct d71_dev* chip_data; int /*<<< orphan*/  dev; } ;
struct d71_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ ,struct d71_dev*) ; 

__attribute__((used)) static void d71_cleanup(struct komeda_dev *mdev)
{
	struct d71_dev *d71 = mdev->chip_data;

	if (!d71)
		return;

	devm_kfree(mdev->dev, d71);
	mdev->chip_data = NULL;
}