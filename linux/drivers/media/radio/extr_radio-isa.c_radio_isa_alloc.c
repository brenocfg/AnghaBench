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
struct v4l2_device {int /*<<< orphan*/  name; } ;
struct radio_isa_driver {TYPE_1__* ops; } ;
struct radio_isa_card {struct v4l2_device v4l2_dev; struct radio_isa_driver* drv; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct radio_isa_card* (* alloc ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct radio_isa_card*) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct radio_isa_card* stub1 () ; 

__attribute__((used)) static struct radio_isa_card *radio_isa_alloc(struct radio_isa_driver *drv,
				struct device *pdev)
{
	struct v4l2_device *v4l2_dev;
	struct radio_isa_card *isa = drv->ops->alloc();
	if (!isa)
		return NULL;

	dev_set_drvdata(pdev, isa);
	isa->drv = drv;
	v4l2_dev = &isa->v4l2_dev;
	strscpy(v4l2_dev->name, dev_name(pdev), sizeof(v4l2_dev->name));

	return isa;
}