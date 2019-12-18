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
struct regulator_config {struct olpc_ec_priv* driver_data; int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct olpc_ec_priv {int dcon_enabled; int /*<<< orphan*/  dbgfs_dir; int /*<<< orphan*/  dcon_rdev; int /*<<< orphan*/  version; int /*<<< orphan*/  cmd_q_lock; int /*<<< orphan*/  cmd_q; int /*<<< orphan*/  cmd_lock; int /*<<< orphan*/  worker; scalar_t__ drv; } ;

/* Variables and functions */
 int /*<<< orphan*/  EC_FIRMWARE_REV ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dcon_desc ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  devm_regulator_register (TYPE_1__*,int /*<<< orphan*/ *,struct regulator_config*) ; 
 scalar_t__ ec_driver ; 
 struct olpc_ec_priv* ec_priv ; 
 int /*<<< orphan*/  kfree (struct olpc_ec_priv*) ; 
 struct olpc_ec_priv* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int olpc_ec_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  olpc_ec_setup_debugfs () ; 
 int /*<<< orphan*/  olpc_ec_worker ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct olpc_ec_priv*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int olpc_ec_probe(struct platform_device *pdev)
{
	struct olpc_ec_priv *ec;
	struct regulator_config config = { };
	int err;

	if (!ec_driver)
		return -ENODEV;

	ec = kzalloc(sizeof(*ec), GFP_KERNEL);
	if (!ec)
		return -ENOMEM;

	ec->drv = ec_driver;
	INIT_WORK(&ec->worker, olpc_ec_worker);
	mutex_init(&ec->cmd_lock);

	INIT_LIST_HEAD(&ec->cmd_q);
	spin_lock_init(&ec->cmd_q_lock);

	ec_priv = ec;
	platform_set_drvdata(pdev, ec);

	/* get the EC revision */
	err = olpc_ec_cmd(EC_FIRMWARE_REV, NULL, 0, &ec->version, 1);
	if (err) {
		ec_priv = NULL;
		kfree(ec);
		return err;
	}

	config.dev = pdev->dev.parent;
	config.driver_data = ec;
	ec->dcon_enabled = true;
	ec->dcon_rdev = devm_regulator_register(&pdev->dev, &dcon_desc,
								&config);
	if (IS_ERR(ec->dcon_rdev)) {
		dev_err(&pdev->dev, "failed to register DCON regulator\n");
		return PTR_ERR(ec->dcon_rdev);
	}

	ec->dbgfs_dir = olpc_ec_setup_debugfs();

	return err;
}