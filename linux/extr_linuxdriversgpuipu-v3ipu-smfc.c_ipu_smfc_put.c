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
struct ipu_smfc_priv {int /*<<< orphan*/  lock; } ;
struct ipu_smfc {int inuse; struct ipu_smfc_priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void ipu_smfc_put(struct ipu_smfc *smfc)
{
	struct ipu_smfc_priv *priv = smfc->priv;
	unsigned long flags;

	spin_lock_irqsave(&priv->lock, flags);
	smfc->inuse = false;
	spin_unlock_irqrestore(&priv->lock, flags);
}