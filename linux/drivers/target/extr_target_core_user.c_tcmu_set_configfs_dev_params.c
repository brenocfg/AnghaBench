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
typedef  int /*<<< orphan*/  substring_t ;
struct tcmu_dev {int /*<<< orphan*/  nl_reply_supported; int /*<<< orphan*/  dev_size; int /*<<< orphan*/  dev_config; } ;
struct TYPE_2__ {int /*<<< orphan*/  hw_max_sectors; int /*<<< orphan*/  hw_block_size; } ;
struct se_device {TYPE_1__ dev_attrib; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MAX_OPT_ARGS ; 
#define  Opt_dev_config 133 
#define  Opt_dev_size 132 
#define  Opt_hw_block_size 131 
#define  Opt_hw_max_sectors 130 
#define  Opt_max_data_area_mb 129 
#define  Opt_nl_reply_supported 128 
 int /*<<< orphan*/  TCMU_CONFIG_LEN ; 
 struct tcmu_dev* TCMU_DEV (struct se_device*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kstrdup (char const*,int /*<<< orphan*/ ) ; 
 int match_int (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  match_strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int match_token (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int match_u64 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 char* strsep (char**,char*) ; 
 int tcmu_set_dev_attrib (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int tcmu_set_max_blocks_param (struct tcmu_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tokens ; 

__attribute__((used)) static ssize_t tcmu_set_configfs_dev_params(struct se_device *dev,
		const char *page, ssize_t count)
{
	struct tcmu_dev *udev = TCMU_DEV(dev);
	char *orig, *ptr, *opts;
	substring_t args[MAX_OPT_ARGS];
	int ret = 0, token;

	opts = kstrdup(page, GFP_KERNEL);
	if (!opts)
		return -ENOMEM;

	orig = opts;

	while ((ptr = strsep(&opts, ",\n")) != NULL) {
		if (!*ptr)
			continue;

		token = match_token(ptr, tokens, args);
		switch (token) {
		case Opt_dev_config:
			if (match_strlcpy(udev->dev_config, &args[0],
					  TCMU_CONFIG_LEN) == 0) {
				ret = -EINVAL;
				break;
			}
			pr_debug("TCMU: Referencing Path: %s\n", udev->dev_config);
			break;
		case Opt_dev_size:
			ret = match_u64(&args[0], &udev->dev_size);
			if (ret < 0)
				pr_err("match_u64() failed for dev_size=. Error %d.\n",
				       ret);
			break;
		case Opt_hw_block_size:
			ret = tcmu_set_dev_attrib(&args[0],
					&(dev->dev_attrib.hw_block_size));
			break;
		case Opt_hw_max_sectors:
			ret = tcmu_set_dev_attrib(&args[0],
					&(dev->dev_attrib.hw_max_sectors));
			break;
		case Opt_nl_reply_supported:
			ret = match_int(&args[0], &udev->nl_reply_supported);
			if (ret < 0)
				pr_err("match_int() failed for nl_reply_supported=. Error %d.\n",
				       ret);
			break;
		case Opt_max_data_area_mb:
			ret = tcmu_set_max_blocks_param(udev, &args[0]);
			break;
		default:
			break;
		}

		if (ret)
			break;
	}

	kfree(orig);
	return (!ret) ? count : ret;
}