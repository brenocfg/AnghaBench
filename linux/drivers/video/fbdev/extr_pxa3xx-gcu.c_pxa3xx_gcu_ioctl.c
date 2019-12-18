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
struct pxa3xx_gcu_priv {int /*<<< orphan*/  spinlock; } ;
struct file {int dummy; } ;

/* Variables and functions */
 long ENOSYS ; 
#define  PXA3XX_GCU_IOCTL_RESET 129 
#define  PXA3XX_GCU_IOCTL_WAIT_IDLE 128 
 int /*<<< orphan*/  pxa3xx_gcu_reset (struct pxa3xx_gcu_priv*) ; 
 long pxa3xx_gcu_wait_idle (struct pxa3xx_gcu_priv*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct pxa3xx_gcu_priv* to_pxa3xx_gcu_priv (struct file*) ; 

__attribute__((used)) static long
pxa3xx_gcu_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	unsigned long flags;
	struct pxa3xx_gcu_priv *priv = to_pxa3xx_gcu_priv(file);

	switch (cmd) {
	case PXA3XX_GCU_IOCTL_RESET:
		spin_lock_irqsave(&priv->spinlock, flags);
		pxa3xx_gcu_reset(priv);
		spin_unlock_irqrestore(&priv->spinlock, flags);
		return 0;

	case PXA3XX_GCU_IOCTL_WAIT_IDLE:
		return pxa3xx_gcu_wait_idle(priv);
	}

	return -ENOSYS;
}