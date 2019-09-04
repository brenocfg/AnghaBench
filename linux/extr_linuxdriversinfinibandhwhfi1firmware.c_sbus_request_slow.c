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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct hfi1_devdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASIC_CFG_SBUS_EXECUTE ; 
 int /*<<< orphan*/  ASIC_CFG_SBUS_EXECUTE_EXECUTE_SMASK ; 
 int /*<<< orphan*/  ASIC_STS_SBUS_COUNTERS ; 
 int /*<<< orphan*/  ASIC_STS_SBUS_RESULT ; 
 int ASIC_STS_SBUS_RESULT_DONE_SMASK ; 
 int ASIC_STS_SBUS_RESULT_RCV_DATA_VALID_SMASK ; 
 int ETIME ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  EXECUTE ; 
 int /*<<< orphan*/  RCV_DATA_VALID ; 
 scalar_t__ SBUS_COUNTER (int,int /*<<< orphan*/ ) ; 
 scalar_t__ SBUS_MAX_POLL_COUNT ; 
 int /*<<< orphan*/  clear_sbus_fast_mode (struct hfi1_devdata*) ; 
 int read_csr (struct hfi1_devdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbus_request (struct hfi1_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  write_csr (struct hfi1_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int sbus_request_slow(struct hfi1_devdata *dd,
		      u8 receiver_addr, u8 data_addr, u8 command, u32 data_in)
{
	u64 reg, count = 0;

	/* make sure fast mode is clear */
	clear_sbus_fast_mode(dd);

	sbus_request(dd, receiver_addr, data_addr, command, data_in);
	write_csr(dd, ASIC_CFG_SBUS_EXECUTE,
		  ASIC_CFG_SBUS_EXECUTE_EXECUTE_SMASK);
	/* Wait for both DONE and RCV_DATA_VALID to go high */
	reg = read_csr(dd, ASIC_STS_SBUS_RESULT);
	while (!((reg & ASIC_STS_SBUS_RESULT_DONE_SMASK) &&
		 (reg & ASIC_STS_SBUS_RESULT_RCV_DATA_VALID_SMASK))) {
		if (count++ >= SBUS_MAX_POLL_COUNT) {
			u64 counts = read_csr(dd, ASIC_STS_SBUS_COUNTERS);
			/*
			 * If the loop has timed out, we are OK if DONE bit
			 * is set and RCV_DATA_VALID and EXECUTE counters
			 * are the same. If not, we cannot proceed.
			 */
			if ((reg & ASIC_STS_SBUS_RESULT_DONE_SMASK) &&
			    (SBUS_COUNTER(counts, RCV_DATA_VALID) ==
			     SBUS_COUNTER(counts, EXECUTE)))
				break;
			return -ETIMEDOUT;
		}
		udelay(1);
		reg = read_csr(dd, ASIC_STS_SBUS_RESULT);
	}
	count = 0;
	write_csr(dd, ASIC_CFG_SBUS_EXECUTE, 0);
	/* Wait for DONE to clear after EXECUTE is cleared */
	reg = read_csr(dd, ASIC_STS_SBUS_RESULT);
	while (reg & ASIC_STS_SBUS_RESULT_DONE_SMASK) {
		if (count++ >= SBUS_MAX_POLL_COUNT)
			return -ETIME;
		udelay(1);
		reg = read_csr(dd, ASIC_STS_SBUS_RESULT);
	}
	return 0;
}