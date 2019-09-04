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
struct TYPE_2__ {int /*<<< orphan*/  otables; } ;
struct vmw_private {TYPE_1__ otable_batch; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmw_otable_batch_takedown (struct vmw_private*,TYPE_1__*) ; 

void vmw_otables_takedown(struct vmw_private *dev_priv)
{
	vmw_otable_batch_takedown(dev_priv, &dev_priv->otable_batch);
	kfree(dev_priv->otable_batch.otables);
}