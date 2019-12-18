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
typedef  int /*<<< orphan*/  u32 ;
struct imx_mu_priv {int /*<<< orphan*/  xcr_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMX_MU_xCR ; 
 int /*<<< orphan*/  imx_mu_read (struct imx_mu_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx_mu_write (struct imx_mu_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static u32 imx_mu_xcr_rmw(struct imx_mu_priv *priv, u32 set, u32 clr)
{
	unsigned long flags;
	u32 val;

	spin_lock_irqsave(&priv->xcr_lock, flags);
	val = imx_mu_read(priv, IMX_MU_xCR);
	val &= ~clr;
	val |= set;
	imx_mu_write(priv, val, IMX_MU_xCR);
	spin_unlock_irqrestore(&priv->xcr_lock, flags);

	return val;
}