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
struct r5conf {scalar_t__ hash_locks; int /*<<< orphan*/  device_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (scalar_t__) ; 

__attribute__((used)) static inline void unlock_device_hash_lock(struct r5conf *conf, int hash)
{
	spin_unlock(&conf->device_lock);
	spin_unlock_irq(conf->hash_locks + hash);
}