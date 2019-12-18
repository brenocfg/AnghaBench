#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct lima_ip {TYPE_1__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIMA_L2_CACHE_COMMAND ; 
 int /*<<< orphan*/  LIMA_L2_CACHE_COMMAND_CLEAR_ALL ; 
 int /*<<< orphan*/  l2_cache_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int lima_l2_cache_wait_idle (struct lima_ip*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int lima_l2_cache_flush(struct lima_ip *ip)
{
	int ret;

	spin_lock(&ip->data.lock);
	l2_cache_write(LIMA_L2_CACHE_COMMAND, LIMA_L2_CACHE_COMMAND_CLEAR_ALL);
	ret = lima_l2_cache_wait_idle(ip);
	spin_unlock(&ip->data.lock);
	return ret;
}