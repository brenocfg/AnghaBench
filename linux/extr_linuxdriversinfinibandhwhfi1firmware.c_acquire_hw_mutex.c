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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct hfi1_devdata {int hfi1_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASIC_CFG_MUTEX ; 
 int EBUSY ; 
 int /*<<< orphan*/  HM_TIMEOUT ; 
 int /*<<< orphan*/  dd_dev_err (struct hfi1_devdata*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dd_dev_info (struct hfi1_devdata*,char*,int /*<<< orphan*/ ) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ read_csr (struct hfi1_devdata*,int /*<<< orphan*/ ) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  write_csr (struct hfi1_devdata*,int /*<<< orphan*/ ,scalar_t__) ; 

int acquire_hw_mutex(struct hfi1_devdata *dd)
{
	unsigned long timeout;
	int try = 0;
	u8 mask = 1 << dd->hfi1_id;
	u8 user = (u8)read_csr(dd, ASIC_CFG_MUTEX);

	if (user == mask) {
		dd_dev_info(dd,
			    "Hardware mutex already acquired, mutex mask %u\n",
			    (u32)mask);
		return 0;
	}

retry:
	timeout = msecs_to_jiffies(HM_TIMEOUT) + jiffies;
	while (1) {
		write_csr(dd, ASIC_CFG_MUTEX, mask);
		user = (u8)read_csr(dd, ASIC_CFG_MUTEX);
		if (user == mask)
			return 0; /* success */
		if (time_after(jiffies, timeout))
			break; /* timed out */
		msleep(20);
	}

	/* timed out */
	dd_dev_err(dd,
		   "Unable to acquire hardware mutex, mutex mask %u, my mask %u (%s)\n",
		   (u32)user, (u32)mask, (try == 0) ? "retrying" : "giving up");

	if (try == 0) {
		/* break mutex and retry */
		write_csr(dd, ASIC_CFG_MUTEX, 0);
		try++;
		goto retry;
	}

	return -EBUSY;
}