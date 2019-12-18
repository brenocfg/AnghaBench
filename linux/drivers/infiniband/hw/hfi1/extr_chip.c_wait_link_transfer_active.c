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
typedef  scalar_t__ u64 ;
struct hfi1_devdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_LCB_STS_LINK_TRANSFER_ACTIVE ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  dd_dev_err (struct hfi1_devdata*,char*) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 scalar_t__ read_csr (struct hfi1_devdata*,int /*<<< orphan*/ ) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int wait_link_transfer_active(struct hfi1_devdata *dd, int wait_ms)
{
	u64 reg;
	unsigned long timeout;

	/* watch LCB_STS_LINK_TRANSFER_ACTIVE */
	timeout = jiffies + msecs_to_jiffies(wait_ms);
	while (1) {
		reg = read_csr(dd, DC_LCB_STS_LINK_TRANSFER_ACTIVE);
		if (reg)
			break;
		if (time_after(jiffies, timeout)) {
			dd_dev_err(dd,
				   "timeout waiting for LINK_TRANSFER_ACTIVE\n");
			return -ETIMEDOUT;
		}
		udelay(2);
	}
	return 0;
}