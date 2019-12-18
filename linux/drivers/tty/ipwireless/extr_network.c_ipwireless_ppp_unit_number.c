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
struct ipw_network {int /*<<< orphan*/  lock; int /*<<< orphan*/ * ppp_channel; } ;

/* Variables and functions */
 int ppp_unit_number (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int ipwireless_ppp_unit_number(struct ipw_network *network)
{
	int ret = -1;
	unsigned long flags;

	spin_lock_irqsave(&network->lock, flags);
	if (network->ppp_channel != NULL)
		ret = ppp_unit_number(network->ppp_channel);
	spin_unlock_irqrestore(&network->lock, flags);

	return ret;
}