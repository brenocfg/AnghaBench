#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct device {TYPE_1__* driver; } ;
struct TYPE_5__ {struct device* parent; } ;
struct TYPE_6__ {TYPE_2__ dev; } ;
struct cec_adapter {TYPE_3__ devnode; int /*<<< orphan*/  owner; } ;
struct TYPE_4__ {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR_OR_NULL (struct cec_adapter*) ; 
 scalar_t__ WARN_ON (int) ; 
 int cec_devnode_register (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_2__*,struct cec_adapter*) ; 

int cec_register_adapter(struct cec_adapter *adap,
			 struct device *parent)
{
	int res;

	if (IS_ERR_OR_NULL(adap))
		return 0;

	if (WARN_ON(!parent))
		return -EINVAL;

	adap->owner = parent->driver->owner;
	adap->devnode.dev.parent = parent;

#ifdef CONFIG_MEDIA_CEC_RC
	if (adap->capabilities & CEC_CAP_RC) {
		adap->rc->dev.parent = parent;
		res = rc_register_device(adap->rc);

		if (res) {
			pr_err("cec-%s: failed to prepare input device\n",
			       adap->name);
			rc_free_device(adap->rc);
			adap->rc = NULL;
			return res;
		}
	}
#endif

	res = cec_devnode_register(&adap->devnode, adap->owner);
	if (res) {
#ifdef CONFIG_MEDIA_CEC_RC
		/* Note: rc_unregister also calls rc_free */
		rc_unregister_device(adap->rc);
		adap->rc = NULL;
#endif
		return res;
	}

	dev_set_drvdata(&adap->devnode.dev, adap);
#ifdef CONFIG_DEBUG_FS
	if (!top_cec_dir)
		return 0;

	adap->cec_dir = debugfs_create_dir(dev_name(&adap->devnode.dev), top_cec_dir);
	if (IS_ERR_OR_NULL(adap->cec_dir)) {
		pr_warn("cec-%s: Failed to create debugfs dir\n", adap->name);
		return 0;
	}
	adap->status_file = debugfs_create_devm_seqfile(&adap->devnode.dev,
		"status", adap->cec_dir, cec_adap_status);
	if (IS_ERR_OR_NULL(adap->status_file)) {
		pr_warn("cec-%s: Failed to create status file\n", adap->name);
		debugfs_remove_recursive(adap->cec_dir);
		adap->cec_dir = NULL;
		return 0;
	}
	if (!adap->ops->error_inj_show || !adap->ops->error_inj_parse_line)
		return 0;
	adap->error_inj_file = debugfs_create_file("error-inj", 0644,
						   adap->cec_dir, adap,
						   &cec_error_inj_fops);
	if (IS_ERR_OR_NULL(adap->error_inj_file))
		pr_warn("cec-%s: Failed to create error-inj file\n",
			adap->name);
#endif
	return 0;
}