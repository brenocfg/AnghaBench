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
struct net_device {int dummy; } ;
struct ipoib_dev_priv {int /*<<< orphan*/ * path_dentry; int /*<<< orphan*/ * mcg_dentry; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove (int /*<<< orphan*/ *) ; 
 struct ipoib_dev_priv* ipoib_priv (struct net_device*) ; 

void ipoib_delete_debug_files(struct net_device *dev)
{
	struct ipoib_dev_priv *priv = ipoib_priv(dev);

	debugfs_remove(priv->mcg_dentry);
	debugfs_remove(priv->path_dentry);
	priv->mcg_dentry = priv->path_dentry = NULL;
}