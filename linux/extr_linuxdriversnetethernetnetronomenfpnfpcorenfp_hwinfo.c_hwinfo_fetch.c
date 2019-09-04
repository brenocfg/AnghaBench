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
struct nfp_hwinfo {int dummy; } ;
struct nfp_cpp {int dummy; } ;

/* Variables and functions */
 unsigned long HWINFO_WAIT ; 
 unsigned long HZ ; 
 struct nfp_hwinfo* hwinfo_try_fetch (struct nfp_cpp*,size_t*) ; 
 unsigned long jiffies ; 
 int msleep_interruptible (int) ; 
 int /*<<< orphan*/  nfp_err (struct nfp_cpp*,char*) ; 
 scalar_t__ time_after (unsigned long const,unsigned long const) ; 

__attribute__((used)) static struct nfp_hwinfo *hwinfo_fetch(struct nfp_cpp *cpp, size_t *hwdb_size)
{
	const unsigned long wait_until = jiffies + HWINFO_WAIT * HZ;
	struct nfp_hwinfo *db;
	int err;

	for (;;) {
		const unsigned long start_time = jiffies;

		db = hwinfo_try_fetch(cpp, hwdb_size);
		if (db)
			return db;

		err = msleep_interruptible(100);
		if (err || time_after(start_time, wait_until)) {
			nfp_err(cpp, "NFP access error\n");
			return NULL;
		}
	}
}