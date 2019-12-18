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
struct vmw_resource {int id; TYPE_1__* func; struct vmw_private* dev_priv; } ;
struct vmw_private {int /*<<< orphan*/  resource_lock; struct idr* res_idr; } ;
struct idr {int dummy; } ;
struct TYPE_2__ {size_t res_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  idr_remove (struct idr*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void vmw_resource_release_id(struct vmw_resource *res)
{
	struct vmw_private *dev_priv = res->dev_priv;
	struct idr *idr = &dev_priv->res_idr[res->func->res_type];

	spin_lock(&dev_priv->resource_lock);
	if (res->id != -1)
		idr_remove(idr, res->id);
	res->id = -1;
	spin_unlock(&dev_priv->resource_lock);
}