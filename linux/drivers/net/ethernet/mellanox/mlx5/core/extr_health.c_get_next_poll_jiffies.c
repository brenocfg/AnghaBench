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
typedef  int /*<<< orphan*/  next ;

/* Variables and functions */
 unsigned long HZ ; 
 scalar_t__ MLX5_HEALTH_POLL_INTERVAL ; 
 int /*<<< orphan*/  get_random_bytes (unsigned long*,int) ; 
 scalar_t__ jiffies ; 

__attribute__((used)) static unsigned long get_next_poll_jiffies(void)
{
	unsigned long next;

	get_random_bytes(&next, sizeof(next));
	next %= HZ;
	next += jiffies + MLX5_HEALTH_POLL_INTERVAL;

	return next;
}