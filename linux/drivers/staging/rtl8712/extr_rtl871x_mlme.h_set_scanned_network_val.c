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
struct mlme_priv {int /*<<< orphan*/  lock; int /*<<< orphan*/  num_of_scanned; } ;
typedef  int /*<<< orphan*/  sint ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline void set_scanned_network_val(struct mlme_priv *pmlmepriv,
					     sint val)
{
	unsigned long irqL;

	spin_lock_irqsave(&pmlmepriv->lock, irqL);
	pmlmepriv->num_of_scanned = val;
	spin_unlock_irqrestore(&pmlmepriv->lock, irqL);
}