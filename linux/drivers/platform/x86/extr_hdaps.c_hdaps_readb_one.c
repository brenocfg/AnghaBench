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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int /*<<< orphan*/  __device_complete () ; 
 int __device_refresh_sync () ; 
 int /*<<< orphan*/  hdaps_mtx ; 
 int /*<<< orphan*/  inb (unsigned int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hdaps_readb_one(unsigned int port, u8 *val)
{
	int ret;

	mutex_lock(&hdaps_mtx);

	/* do a sync refresh -- we need to be sure that we read fresh data */
	ret = __device_refresh_sync();
	if (ret)
		goto out;

	*val = inb(port);
	__device_complete();

out:
	mutex_unlock(&hdaps_mtx);
	return ret;
}