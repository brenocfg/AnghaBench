#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  kobj; } ;
struct platform_device {int /*<<< orphan*/ * resource; TYPE_1__ dev; } ;
struct env {int /*<<< orphan*/  regs; int /*<<< orphan*/  hwmon_dev; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_SIZE ; 
 struct env* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  env_group ; 
 int /*<<< orphan*/  hwmon_device_register (TYPE_1__*) ; 
 int /*<<< orphan*/  of_ioremap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  of_iounmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct env*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int env_probe(struct platform_device *op)
{
	struct env *p = devm_kzalloc(&op->dev, sizeof(*p), GFP_KERNEL);
	int err = -ENOMEM;

	if (!p)
		goto out;

	spin_lock_init(&p->lock);

	p->regs = of_ioremap(&op->resource[0], 0, REG_SIZE, "pic16f747");
	if (!p->regs)
		goto out;

	err = sysfs_create_group(&op->dev.kobj, &env_group);
	if (err)
		goto out_iounmap;

	p->hwmon_dev = hwmon_device_register(&op->dev);
	if (IS_ERR(p->hwmon_dev)) {
		err = PTR_ERR(p->hwmon_dev);
		goto out_sysfs_remove_group;
	}

	platform_set_drvdata(op, p);
	err = 0;

out:
	return err;

out_sysfs_remove_group:
	sysfs_remove_group(&op->dev.kobj, &env_group);

out_iounmap:
	of_iounmap(&op->resource[0], p->regs, REG_SIZE);

	goto out;
}