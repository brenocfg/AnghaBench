#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mon_private {int /*<<< orphan*/  path; int /*<<< orphan*/  iucv_connected; int /*<<< orphan*/  iucv_severed; } ;
struct inode {int dummy; } ;
struct file {struct mon_private* private_data; } ;

/* Variables and functions */
 int EBUSY ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IUCV_IPRMDATA ; 
 int /*<<< orphan*/  MON_IN_USE ; 
 int /*<<< orphan*/  MON_MSGLIM ; 
 int /*<<< orphan*/  MON_SERVICE ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ ,struct mon_private*) ; 
 int /*<<< orphan*/  iucv_path_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int iucv_path_connect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct mon_private*) ; 
 int /*<<< orphan*/  iucv_path_free (int /*<<< orphan*/ ) ; 
 struct mon_private* mon_alloc_mem () ; 
 int /*<<< orphan*/  mon_conn_wait_queue ; 
 int /*<<< orphan*/  mon_free_mem (struct mon_private*) ; 
 int /*<<< orphan*/  mon_in_use ; 
 int /*<<< orphan*/  monreader_device ; 
 int /*<<< orphan*/  monreader_iucv_handler ; 
 int nonseekable_open (struct inode*,struct file*) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  user_data_connect ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mon_open(struct inode *inode, struct file *filp)
{
	struct mon_private *monpriv;
	int rc;

	/*
	 * only one user allowed
	 */
	rc = -EBUSY;
	if (test_and_set_bit(MON_IN_USE, &mon_in_use))
		goto out;

	rc = -ENOMEM;
	monpriv = mon_alloc_mem();
	if (!monpriv)
		goto out_use;

	/*
	 * Connect to *MONITOR service
	 */
	monpriv->path = iucv_path_alloc(MON_MSGLIM, IUCV_IPRMDATA, GFP_KERNEL);
	if (!monpriv->path)
		goto out_priv;
	rc = iucv_path_connect(monpriv->path, &monreader_iucv_handler,
			       MON_SERVICE, NULL, user_data_connect, monpriv);
	if (rc) {
		pr_err("Connecting to the z/VM *MONITOR system service "
		       "failed with rc=%i\n", rc);
		rc = -EIO;
		goto out_path;
	}
	/*
	 * Wait for connection confirmation
	 */
	wait_event(mon_conn_wait_queue,
		   atomic_read(&monpriv->iucv_connected) ||
		   atomic_read(&monpriv->iucv_severed));
	if (atomic_read(&monpriv->iucv_severed)) {
		atomic_set(&monpriv->iucv_severed, 0);
		atomic_set(&monpriv->iucv_connected, 0);
		rc = -EIO;
		goto out_path;
	}
	filp->private_data = monpriv;
	dev_set_drvdata(monreader_device, monpriv);
	return nonseekable_open(inode, filp);

out_path:
	iucv_path_free(monpriv->path);
out_priv:
	mon_free_mem(monpriv);
out_use:
	clear_bit(MON_IN_USE, &mon_in_use);
out:
	return rc;
}