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
struct dm_writecache {int flush_on_suspend; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  wc_lock (struct dm_writecache*) ; 
 int /*<<< orphan*/  wc_unlock (struct dm_writecache*) ; 

__attribute__((used)) static int process_flush_on_suspend_mesg(unsigned argc, char **argv, struct dm_writecache *wc)
{
	if (argc != 1)
		return -EINVAL;

	wc_lock(wc);
	wc->flush_on_suspend = true;
	wc_unlock(wc);

	return 0;
}