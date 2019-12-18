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
struct hl_fpriv {int is_control; int /*<<< orphan*/  taskpid; struct file* filp; struct hl_device* hdev; int /*<<< orphan*/  dev_node; } ;
struct hl_device {int /*<<< orphan*/  fpriv_list_lock; int /*<<< orphan*/  fpriv_list; int /*<<< orphan*/  dev_ctrl; } ;
struct file {struct hl_fpriv* private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int EPERM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  dev_err_ratelimited (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_get_pid (int /*<<< orphan*/ ) ; 
 scalar_t__ hl_device_disabled_or_in_reset (struct hl_device*) ; 
 int /*<<< orphan*/  hl_devs_idr ; 
 int /*<<< orphan*/  hl_devs_idr_lock ; 
 struct hl_device* idr_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imajor (struct inode*) ; 
 int /*<<< orphan*/  iminor (struct inode*) ; 
 int /*<<< orphan*/  kfree (struct hl_fpriv*) ; 
 struct hl_fpriv* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nonseekable_open (struct inode*,struct file*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int hl_device_open_ctrl(struct inode *inode, struct file *filp)
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

	mutex_lock(&hdev->fpriv_list_lock);

	if (hl_device_disabled_or_in_reset(hdev)) {
		dev_err_ratelimited(hdev->dev_ctrl,
			"Can't open %s because it is disabled or in reset\n",
			dev_name(hdev->dev_ctrl));
		rc = -EPERM;
		goto out_err;
	}

	list_add(&hpriv->dev_node, &hdev->fpriv_list);
	mutex_unlock(&hdev->fpriv_list_lock);

	hpriv->hdev = hdev;
	filp->private_data = hpriv;
	hpriv->filp = filp;
	hpriv->is_control = true;
	nonseekable_open(inode, filp);

	hpriv->taskpid = find_get_pid(current->pid);

	return 0;

out_err:
	mutex_unlock(&hdev->fpriv_list_lock);
	kfree(hpriv);
	return rc;
}