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
struct vmw_resource {int id; struct vmw_private* dev_priv; } ;
struct vmw_private {int /*<<< orphan*/  binding_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmw_view_destroy (struct vmw_resource*) ; 

__attribute__((used)) static void vmw_hw_view_destroy(struct vmw_resource *res)
{
	struct vmw_private *dev_priv = res->dev_priv;

	mutex_lock(&dev_priv->binding_mutex);
	WARN_ON(vmw_view_destroy(res));
	res->id = -1;
	mutex_unlock(&dev_priv->binding_mutex);
}