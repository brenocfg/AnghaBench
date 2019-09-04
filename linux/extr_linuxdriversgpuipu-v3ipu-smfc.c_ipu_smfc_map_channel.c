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
typedef  int u32 ;
struct ipu_smfc_priv {int /*<<< orphan*/  lock; scalar_t__ base; } ;
struct ipu_smfc {int chno; struct ipu_smfc_priv* priv; } ;

/* Variables and functions */
 scalar_t__ SMFC_MAP ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

int ipu_smfc_map_channel(struct ipu_smfc *smfc, int csi_id, int mipi_id)
{
	struct ipu_smfc_priv *priv = smfc->priv;
	unsigned long flags;
	u32 val, shift;

	spin_lock_irqsave(&priv->lock, flags);

	shift = smfc->chno * 3;
	val = readl(priv->base + SMFC_MAP);
	val &= ~(0x7 << shift);
	val |= ((csi_id << 2) | mipi_id) << shift;
	writel(val, priv->base + SMFC_MAP);

	spin_unlock_irqrestore(&priv->lock, flags);

	return 0;
}