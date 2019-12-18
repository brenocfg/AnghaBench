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
struct tb {int /*<<< orphan*/  lock; int /*<<< orphan*/  root_switch; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ tb_free_unplugged_xdomains (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tb_scan_switch (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tb_complete(struct tb *tb)
{
	/*
	 * Release any unplugged XDomains and if there is a case where
	 * another domain is swapped in place of unplugged XDomain we
	 * need to run another rescan.
	 */
	mutex_lock(&tb->lock);
	if (tb_free_unplugged_xdomains(tb->root_switch))
		tb_scan_switch(tb->root_switch);
	mutex_unlock(&tb->lock);
}