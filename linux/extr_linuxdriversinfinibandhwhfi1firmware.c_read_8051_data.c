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
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
struct hfi1_devdata {int /*<<< orphan*/  dc8051_memlock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_DC8051_CFG_RAM_ACCESS_CTRL ; 
 int /*<<< orphan*/  DC_DC8051_CFG_RAM_ACCESS_SETUP ; 
 int __read_8051_data (struct hfi1_devdata*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_csr (struct hfi1_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int read_8051_data(struct hfi1_devdata *dd, u32 addr, u32 len, u64 *result)
{
	unsigned long flags;
	u32 done;
	int ret = 0;

	spin_lock_irqsave(&dd->dc8051_memlock, flags);

	/* data read set-up, no auto-increment */
	write_csr(dd, DC_DC8051_CFG_RAM_ACCESS_SETUP, 0);

	for (done = 0; done < len; addr += 8, done += 8, result++) {
		ret = __read_8051_data(dd, addr, result);
		if (ret)
			break;
	}

	/* turn off read enable */
	write_csr(dd, DC_DC8051_CFG_RAM_ACCESS_CTRL, 0);

	spin_unlock_irqrestore(&dd->dc8051_memlock, flags);

	return ret;
}