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
struct komeda_dev {int /*<<< orphan*/  dev; } ;
struct komeda_component {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ ,struct komeda_component*) ; 

void komeda_component_destroy(struct komeda_dev *mdev,
			      struct komeda_component *c)
{
	devm_kfree(mdev->dev, c);
}