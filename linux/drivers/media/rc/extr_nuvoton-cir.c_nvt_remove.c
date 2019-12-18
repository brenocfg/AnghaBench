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
struct pnp_dev {int dummy; } ;
struct nvt_dev {TYPE_1__* rdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_attr_wakeup_data ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvt_disable_cir (struct nvt_dev*) ; 
 int /*<<< orphan*/  nvt_enable_wake (struct nvt_dev*) ; 
 struct nvt_dev* pnp_get_drvdata (struct pnp_dev*) ; 

__attribute__((used)) static void nvt_remove(struct pnp_dev *pdev)
{
	struct nvt_dev *nvt = pnp_get_drvdata(pdev);

	device_remove_file(&nvt->rdev->dev, &dev_attr_wakeup_data);

	nvt_disable_cir(nvt);

	/* enable CIR Wake (for IR power-on) */
	nvt_enable_wake(nvt);
}