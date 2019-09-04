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
struct client {int /*<<< orphan*/  lock; int /*<<< orphan*/  resource_idr; } ;

/* Variables and functions */
 int idr_for_each (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_outbound_transaction_resource ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int has_outbound_transactions(struct client *client)
{
	int ret;

	spin_lock_irq(&client->lock);
	ret = idr_for_each(&client->resource_idr,
			   is_outbound_transaction_resource, NULL);
	spin_unlock_irq(&client->lock);

	return ret;
}