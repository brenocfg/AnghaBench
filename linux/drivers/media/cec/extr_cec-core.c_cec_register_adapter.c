#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct device {TYPE_1__* driver; } ;
struct TYPE_16__ {struct device* parent; } ;
struct TYPE_11__ {TYPE_7__ dev; } ;
struct cec_adapter {int capabilities; int /*<<< orphan*/  name; struct cec_adapter* error_inj_file; struct cec_adapter* cec_dir; TYPE_3__* ops; struct cec_adapter* status_file; TYPE_10__ devnode; TYPE_4__* rc; int /*<<< orphan*/  owner; } ;
struct TYPE_13__ {struct device* parent; } ;
struct TYPE_15__ {TYPE_2__ dev; } ;
struct TYPE_14__ {int /*<<< orphan*/  error_inj_parse_line; int /*<<< orphan*/  error_inj_show; } ;
struct TYPE_12__ {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int CEC_CAP_RC ; 
 int EINVAL ; 
 scalar_t__ IS_ERR_OR_NULL (struct cec_adapter*) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  cec_adap_status ; 
 int cec_devnode_register (TYPE_10__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cec_error_inj_fops ; 
 struct cec_adapter* debugfs_create_devm_seqfile (TYPE_7__*,char*,struct cec_adapter*,int /*<<< orphan*/ ) ; 
 struct cec_adapter* debugfs_create_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cec_adapter* debugfs_create_file (char*,int,struct cec_adapter*,struct cec_adapter*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_remove_recursive (struct cec_adapter*) ; 
 int /*<<< orphan*/  dev_name (TYPE_7__*) ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_7__*,struct cec_adapter*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rc_free_device (TYPE_4__*) ; 
 int rc_register_device (TYPE_4__*) ; 
 int /*<<< orphan*/  rc_unregister_device (TYPE_4__*) ; 
 int /*<<< orphan*/  top_cec_dir ; 

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