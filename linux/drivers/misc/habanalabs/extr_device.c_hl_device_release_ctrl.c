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
struct inode {int dummy; } ;
struct hl_fpriv {int /*<<< orphan*/  dev_node; struct hl_device* hdev; } ;
struct hl_device {int /*<<< orphan*/  fpriv_list_lock; } ;
struct file {struct hl_fpriv* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct hl_fpriv*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hl_device_release_ctrl(struct inode *inode, struct file *filp)
{
	struct hl_fpriv *hpriv = filp->private_data;
	struct hl_device *hdev;

	filp->private_data = NULL;

	hdev = hpriv->hdev;

	mutex_lock(&hdev->fpriv_list_lock);
	list_del(&hpriv->dev_node);
	mutex_unlock(&hdev->fpriv_list_lock);

	kfree(hpriv);

	return 0;
}