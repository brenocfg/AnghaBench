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
typedef  int /*<<< orphan*/  u16 ;
struct w5300_priv {int /*<<< orphan*/  reg_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  W5300_IDM_AR ; 
 int /*<<< orphan*/  W5300_IDM_DR ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  w5300_write_direct (struct w5300_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void w5300_write_indirect(struct w5300_priv *priv, u16 addr, u16 data)
{
	unsigned long flags;

	spin_lock_irqsave(&priv->reg_lock, flags);
	w5300_write_direct(priv, W5300_IDM_AR, addr);
	w5300_write_direct(priv, W5300_IDM_DR, data);
	spin_unlock_irqrestore(&priv->reg_lock, flags);
}