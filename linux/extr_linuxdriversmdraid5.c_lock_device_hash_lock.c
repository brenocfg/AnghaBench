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
struct r5conf {int /*<<< orphan*/  device_lock; scalar_t__ hash_locks; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (scalar_t__) ; 

__attribute__((used)) static inline void lock_device_hash_lock(struct r5conf *conf, int hash)
{
	spin_lock_irq(conf->hash_locks + hash);
	spin_lock(&conf->device_lock);
}