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
struct vmw_private {TYPE_1__* ldu_priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  active; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOSYS ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

int vmw_kms_ldu_close_display(struct vmw_private *dev_priv)
{
	if (!dev_priv->ldu_priv)
		return -ENOSYS;

	BUG_ON(!list_empty(&dev_priv->ldu_priv->active));

	kfree(dev_priv->ldu_priv);

	return 0;
}