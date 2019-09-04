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
 int /*<<< orphan*/  ASIC_CFG_SBUS_EXECUTE ; 
 int /*<<< orphan*/  ASIC_STS_SBUS_COUNTERS ; 
 int /*<<< orphan*/  EXECUTE ; 
 int /*<<< orphan*/  RCV_DATA_VALID ; 
 scalar_t__ SBUS_COUNTER (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ SBUS_MAX_POLL_COUNT ; 
 scalar_t__ read_csr (struct hfi1_devdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  write_csr (struct hfi1_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void clear_sbus_fast_mode(struct hfi1_devdata *dd)
{
	u64 reg, count = 0;

	reg = read_csr(dd, ASIC_STS_SBUS_COUNTERS);
	while (SBUS_COUNTER(reg, EXECUTE) !=
	       SBUS_COUNTER(reg, RCV_DATA_VALID)) {
		if (count++ >= SBUS_MAX_POLL_COUNT)
			break;
		udelay(1);
		reg = read_csr(dd, ASIC_STS_SBUS_COUNTERS);
	}
	write_csr(dd, ASIC_CFG_SBUS_EXECUTE, 0);
}