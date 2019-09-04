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
typedef  int u64 ;
struct hfi1_devdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCE_CTRL ; 
 int /*<<< orphan*/  CCE_STATUS ; 
 int /*<<< orphan*/  CCE_STATUS_TIMEOUT ; 
 int /*<<< orphan*/  dd_dev_err (struct hfi1_devdata*,char*,int,int) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int read_csr (struct hfi1_devdata*,int /*<<< orphan*/ ) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  write_csr (struct hfi1_devdata*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void clear_cce_status(struct hfi1_devdata *dd, u64 status_bits,
			     u64 ctrl_bits)
{
	unsigned long timeout;
	u64 reg;

	/* is the condition present? */
	reg = read_csr(dd, CCE_STATUS);
	if ((reg & status_bits) == 0)
		return;

	/* clear the condition */
	write_csr(dd, CCE_CTRL, ctrl_bits);

	/* wait for the condition to clear */
	timeout = jiffies + msecs_to_jiffies(CCE_STATUS_TIMEOUT);
	while (1) {
		reg = read_csr(dd, CCE_STATUS);
		if ((reg & status_bits) == 0)
			return;
		if (time_after(jiffies, timeout)) {
			dd_dev_err(dd,
				   "Timeout waiting for CceStatus to clear bits 0x%llx, remaining 0x%llx\n",
				   status_bits, reg & status_bits);
			return;
		}
		udelay(1);
	}
}