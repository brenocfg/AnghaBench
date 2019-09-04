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
struct gpio_mockup_dbgfs_private {int offset; int /*<<< orphan*/ * desc; struct gpio_mockup_chip* chip; } ;
struct gpio_chip {int ngpio; TYPE_1__* gpiodev; int /*<<< orphan*/  label; } ;
struct gpio_mockup_chip {struct dentry* dbg_dir; struct gpio_chip gc; } ;
struct device {int dummy; } ;
struct dentry {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * descs; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR_OR_NULL (struct dentry*) ; 
 struct dentry* debugfs_create_dir (char const*,int /*<<< orphan*/ ) ; 
 struct dentry* debugfs_create_file (char*,int,struct dentry*,struct gpio_mockup_dbgfs_private*,int /*<<< orphan*/ *) ; 
 struct dentry* debugfs_create_symlink (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 char* dev_name (int /*<<< orphan*/ *) ; 
 char* devm_kasprintf (struct device*,int /*<<< orphan*/ ,char*,int) ; 
 struct gpio_mockup_dbgfs_private* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_mockup_dbg_dir ; 
 int /*<<< orphan*/  gpio_mockup_event_ops ; 

__attribute__((used)) static void gpio_mockup_debugfs_setup(struct device *dev,
				      struct gpio_mockup_chip *chip)
{
	struct gpio_mockup_dbgfs_private *priv;
	struct dentry *evfile, *link;
	struct gpio_chip *gc;
	const char *devname;
	char *name;
	int i;

	gc = &chip->gc;
	devname = dev_name(&gc->gpiodev->dev);

	chip->dbg_dir = debugfs_create_dir(devname, gpio_mockup_dbg_dir);
	if (IS_ERR_OR_NULL(chip->dbg_dir))
		goto err;

	link = debugfs_create_symlink(gc->label, gpio_mockup_dbg_dir, devname);
	if (IS_ERR_OR_NULL(link))
		goto err;

	for (i = 0; i < gc->ngpio; i++) {
		name = devm_kasprintf(dev, GFP_KERNEL, "%d", i);
		if (!name)
			goto err;

		priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
		if (!priv)
			goto err;

		priv->chip = chip;
		priv->offset = i;
		priv->desc = &gc->gpiodev->descs[i];

		evfile = debugfs_create_file(name, 0200, chip->dbg_dir, priv,
					     &gpio_mockup_event_ops);
		if (IS_ERR_OR_NULL(evfile))
			goto err;
	}

	return;

err:
	dev_err(dev, "error creating debugfs event files\n");
}