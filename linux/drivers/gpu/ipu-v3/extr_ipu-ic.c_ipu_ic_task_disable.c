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
typedef  int u32 ;
struct ipu_ic_priv {int /*<<< orphan*/  lock; } ;
struct ipu_ic {TYPE_1__* bit; struct ipu_ic_priv* priv; } ;
struct TYPE_2__ {int ic_conf_en; int ic_conf_csc1_en; int ic_conf_rot_en; int ic_conf_csc2_en; int ic_conf_cmb_en; } ;

/* Variables and functions */
 int /*<<< orphan*/  IC_CONF ; 
 int ipu_ic_read (struct ipu_ic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_ic_write (struct ipu_ic*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void ipu_ic_task_disable(struct ipu_ic *ic)
{
	struct ipu_ic_priv *priv = ic->priv;
	unsigned long flags;
	u32 ic_conf;

	spin_lock_irqsave(&priv->lock, flags);

	ic_conf = ipu_ic_read(ic, IC_CONF);

	ic_conf &= ~(ic->bit->ic_conf_en |
		     ic->bit->ic_conf_csc1_en |
		     ic->bit->ic_conf_rot_en);
	if (ic->bit->ic_conf_csc2_en)
		ic_conf &= ~ic->bit->ic_conf_csc2_en;
	if (ic->bit->ic_conf_cmb_en)
		ic_conf &= ~ic->bit->ic_conf_cmb_en;

	ipu_ic_write(ic, ic_conf, IC_CONF);

	spin_unlock_irqrestore(&priv->lock, flags);
}