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
struct p54p_priv {int /*<<< orphan*/  boot_comp; int /*<<< orphan*/  tasklet; } ;
struct ieee80211_hw {struct p54p_priv* priv; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
typedef  int __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int ISL38XX_INT_IDENT_INIT ; 
 int ISL38XX_INT_IDENT_UPDATE ; 
 int P54P_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  P54P_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int cpu_to_le32 (int) ; 
 int /*<<< orphan*/  int_ack ; 
 int /*<<< orphan*/  int_enable ; 
 int /*<<< orphan*/  int_ident ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static irqreturn_t p54p_interrupt(int irq, void *dev_id)
{
	struct ieee80211_hw *dev = dev_id;
	struct p54p_priv *priv = dev->priv;
	__le32 reg;

	reg = P54P_READ(int_ident);
	if (unlikely(reg == cpu_to_le32(0xFFFFFFFF))) {
		goto out;
	}
	P54P_WRITE(int_ack, reg);

	reg &= P54P_READ(int_enable);

	if (reg & cpu_to_le32(ISL38XX_INT_IDENT_UPDATE))
		tasklet_schedule(&priv->tasklet);
	else if (reg & cpu_to_le32(ISL38XX_INT_IDENT_INIT))
		complete(&priv->boot_comp);

out:
	return reg ? IRQ_HANDLED : IRQ_NONE;
}