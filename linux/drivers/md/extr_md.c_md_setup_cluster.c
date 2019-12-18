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
struct mddev {int dummy; } ;
struct TYPE_2__ {int (* join ) (struct mddev*,int) ;} ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  md_cluster_mod ; 
 TYPE_1__* md_cluster_ops ; 
 int /*<<< orphan*/  pers_lock ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  request_module (char*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct mddev*,int) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

int md_setup_cluster(struct mddev *mddev, int nodes)
{
	if (!md_cluster_ops)
		request_module("md-cluster");
	spin_lock(&pers_lock);
	/* ensure module won't be unloaded */
	if (!md_cluster_ops || !try_module_get(md_cluster_mod)) {
		pr_warn("can't find md-cluster module or get it's reference.\n");
		spin_unlock(&pers_lock);
		return -ENOENT;
	}
	spin_unlock(&pers_lock);

	return md_cluster_ops->join(mddev, nodes);
}