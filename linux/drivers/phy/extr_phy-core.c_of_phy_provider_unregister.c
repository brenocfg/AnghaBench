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
struct phy_provider {int /*<<< orphan*/  children; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct phy_provider*) ; 
 int /*<<< orphan*/  kfree (struct phy_provider*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_provider_mutex ; 

void of_phy_provider_unregister(struct phy_provider *phy_provider)
{
	if (IS_ERR(phy_provider))
		return;

	mutex_lock(&phy_provider_mutex);
	list_del(&phy_provider->list);
	of_node_put(phy_provider->children);
	kfree(phy_provider);
	mutex_unlock(&phy_provider_mutex);
}