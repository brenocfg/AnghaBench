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
struct inode {int dummy; } ;
struct hl_fpriv {int /*<<< orphan*/  taskpid; int /*<<< orphan*/  restore_phase_mutex; int /*<<< orphan*/  ctx_mgr; struct hl_device* hdev; int /*<<< orphan*/  cb_mgr; int /*<<< orphan*/  dev_node; int /*<<< orphan*/  refcount; struct file* filp; } ;
struct hl_device {int /*<<< orphan*/  fpriv_list_lock; int /*<<< orphan*/  fpriv_list; int /*<<< orphan*/  dev; scalar_t__ compute_ctx; scalar_t__ in_debug; } ;
struct file {struct hl_fpriv* private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int ENXIO ; 
 int EPERM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PLL_HIGH ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  dev_dbg_ratelimited (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_err_ratelimited (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_get_pid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hl_cb_mgr_fini (struct hl_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hl_cb_mgr_init (int /*<<< orphan*/ *) ; 
 int hl_ctx_create (struct hl_device*,struct hl_fpriv*) ; 
 int /*<<< orphan*/  hl_ctx_mgr_fini (struct hl_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hl_ctx_mgr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hl_debugfs_add_file (struct hl_fpriv*) ; 
 scalar_t__ hl_device_disabled_or_in_reset (struct hl_device*) ; 
 int /*<<< orphan*/  hl_device_set_frequency (struct hl_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hl_devs_idr ; 
 int /*<<< orphan*/  hl_devs_idr_lock ; 
 struct hl_device* idr_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imajor (struct inode*) ; 
 int /*<<< orphan*/  iminor (struct inode*) ; 
 int /*<<< orphan*/  kfree (struct hl_fpriv*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct hl_fpriv* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nonseekable_open (struct inode*,struct file*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_pid (int /*<<< orphan*/ ) ; 

int hl_device_open(struct inode *inode, struct file *filp)
{
	struct hl_device *hdev;
	struct hl_fpriv *hpriv;
	int rc;

	mutex_lock(&hl_devs_idr_lock);
	hdev = idr_find(&hl_devs_idr, iminor(inode));
	mutex_unlock(&hl_devs_idr_lock);

	if (!hdev) {
		pr_err("Couldn't find device %d:%d\n",
			imajor(inode), iminor(inode));
		return -ENXIO;
	}

	hpriv = kzalloc(sizeof(*hpriv), GFP_KERNEL);
	if (!hpriv)
		return -ENOMEM;

	hpriv->hdev = hdev;
	filp->private_data = hpriv;
	hpriv->filp = filp;
	mutex_init(&hpriv->restore_phase_mutex);
	kref_init(&hpriv->refcount);
	nonseekable_open(inode, filp);

	hl_cb_mgr_init(&hpriv->cb_mgr);
	hl_ctx_mgr_init(&hpriv->ctx_mgr);

	hpriv->taskpid = find_get_pid(current->pid);

	mutex_lock(&hdev->fpriv_list_lock);

	if (hl_device_disabled_or_in_reset(hdev)) {
		dev_err_ratelimited(hdev->dev,
			"Can't open %s because it is disabled or in reset\n",
			dev_name(hdev->dev));
		rc = -EPERM;
		goto out_err;
	}

	if (hdev->in_debug) {
		dev_err_ratelimited(hdev->dev,
			"Can't open %s because it is being debugged by another user\n",
			dev_name(hdev->dev));
		rc = -EPERM;
		goto out_err;
	}

	if (hdev->compute_ctx) {
		dev_dbg_ratelimited(hdev->dev,
			"Can't open %s because another user is working on it\n",
			dev_name(hdev->dev));
		rc = -EBUSY;
		goto out_err;
	}

	rc = hl_ctx_create(hdev, hpriv);
	if (rc) {
		dev_err(hdev->dev, "Failed to create context %d\n", rc);
		goto out_err;
	}

	/* Device is IDLE at this point so it is legal to change PLLs.
	 * There is no need to check anything because if the PLL is
	 * already HIGH, the set function will return without doing
	 * anything
	 */
	hl_device_set_frequency(hdev, PLL_HIGH);

	list_add(&hpriv->dev_node, &hdev->fpriv_list);
	mutex_unlock(&hdev->fpriv_list_lock);

	hl_debugfs_add_file(hpriv);

	return 0;

out_err:
	mutex_unlock(&hdev->fpriv_list_lock);

	hl_cb_mgr_fini(hpriv->hdev, &hpriv->cb_mgr);
	hl_ctx_mgr_fini(hpriv->hdev, &hpriv->ctx_mgr);
	filp->private_data = NULL;
	mutex_destroy(&hpriv->restore_phase_mutex);
	put_pid(hpriv->taskpid);

	kfree(hpriv);
	return rc;
}