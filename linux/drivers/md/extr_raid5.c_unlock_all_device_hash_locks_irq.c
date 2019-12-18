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
struct r5conf {int /*<<< orphan*/ * hash_locks; int /*<<< orphan*/  device_lock; } ;

/* Variables and functions */
 int NR_STRIPE_HASH_LOCKS ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void unlock_all_device_hash_locks_irq(struct r5conf *conf)
{
	int i;
	spin_unlock(&conf->device_lock);
	for (i = NR_STRIPE_HASH_LOCKS - 1; i; i--)
		spin_unlock(conf->hash_locks + i);
	spin_unlock_irq(conf->hash_locks);
}