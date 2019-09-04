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
struct ipu_smfc_priv {int /*<<< orphan*/  lock; int /*<<< orphan*/  use_count; int /*<<< orphan*/  ipu; } ;
struct ipu_smfc {struct ipu_smfc_priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPU_CONF_SMFC_EN ; 
 int /*<<< orphan*/  ipu_module_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int ipu_smfc_enable(struct ipu_smfc *smfc)
{
	struct ipu_smfc_priv *priv = smfc->priv;
	unsigned long flags;

	spin_lock_irqsave(&priv->lock, flags);

	if (!priv->use_count)
		ipu_module_enable(priv->ipu, IPU_CONF_SMFC_EN);

	priv->use_count++;

	spin_unlock_irqrestore(&priv->lock, flags);

	return 0;
}