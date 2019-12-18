#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_2__ dev; } ;
struct cros_ec_platform {char* ec_name; } ;
struct cros_ec_dev {struct cros_ec_debugfs* debug_info; TYPE_1__* ec_dev; int /*<<< orphan*/  dev; } ;
struct cros_ec_debugfs {int /*<<< orphan*/  dir; struct cros_ec_dev* ec; } ;
struct TYPE_3__ {int /*<<< orphan*/  last_resume_result; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int cros_ec_create_console_log (struct cros_ec_debugfs*) ; 
 int cros_ec_create_panicinfo (struct cros_ec_debugfs*) ; 
 int /*<<< orphan*/  cros_ec_pdinfo_fops ; 
 int /*<<< orphan*/  cros_ec_uptime_fops ; 
 int /*<<< orphan*/  debugfs_create_dir (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,int /*<<< orphan*/ ,struct cros_ec_debugfs*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_x32 (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ ) ; 
 struct cros_ec_dev* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct cros_ec_platform* dev_get_platdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_2__*,struct cros_ec_dev*) ; 
 struct cros_ec_debugfs* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cros_ec_debugfs_probe(struct platform_device *pd)
{
	struct cros_ec_dev *ec = dev_get_drvdata(pd->dev.parent);
	struct cros_ec_platform *ec_platform = dev_get_platdata(ec->dev);
	const char *name = ec_platform->ec_name;
	struct cros_ec_debugfs *debug_info;
	int ret;

	debug_info = devm_kzalloc(ec->dev, sizeof(*debug_info), GFP_KERNEL);
	if (!debug_info)
		return -ENOMEM;

	debug_info->ec = ec;
	debug_info->dir = debugfs_create_dir(name, NULL);

	ret = cros_ec_create_panicinfo(debug_info);
	if (ret)
		goto remove_debugfs;

	ret = cros_ec_create_console_log(debug_info);
	if (ret)
		goto remove_debugfs;

	debugfs_create_file("pdinfo", 0444, debug_info->dir, debug_info,
			    &cros_ec_pdinfo_fops);

	debugfs_create_file("uptime", 0444, debug_info->dir, debug_info,
			    &cros_ec_uptime_fops);

	debugfs_create_x32("last_resume_result", 0444, debug_info->dir,
			   &ec->ec_dev->last_resume_result);

	ec->debug_info = debug_info;

	dev_set_drvdata(&pd->dev, ec);

	return 0;

remove_debugfs:
	debugfs_remove_recursive(debug_info->dir);
	return ret;
}