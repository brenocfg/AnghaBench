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
struct nbu2ss_udc {int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  _nbu2ss_check_vbus (struct nbu2ss_udc*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t _nbu2ss_vbus_irq(int irq, void *_udc)
{
	struct nbu2ss_udc	*udc = (struct nbu2ss_udc *)_udc;

	spin_lock(&udc->lock);
	_nbu2ss_check_vbus(udc);
	spin_unlock(&udc->lock);

	return IRQ_HANDLED;
}