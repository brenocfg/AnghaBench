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
typedef  int uint64_t ;
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 int MAX_RDR_WORDS ; 
 scalar_t__ ONYX_INTF ; 
 int /*<<< orphan*/  perf_intrigue_disable_perf_counters () ; 
 scalar_t__ perf_processor_interface ; 
 int /*<<< orphan*/  perf_rdr_clear (int) ; 
 int /*<<< orphan*/  perf_rdr_read_ubuf (int,int*) ; 
 int /*<<< orphan*/  perf_rdr_write (int,int*) ; 

__attribute__((used)) static int perf_stop_counters(uint32_t *raddr)
{
	uint64_t userbuf[MAX_RDR_WORDS];

	/* Disable performance counters */
	perf_intrigue_disable_perf_counters();

	if (perf_processor_interface == ONYX_INTF) {
		uint64_t tmp64;
		/*
		 * Read the counters
		 */
		if (!perf_rdr_read_ubuf(16, userbuf))
			return -13;

		/* Counter0 is bits 1398 to 1429 */
		tmp64 =  (userbuf[21] << 22) & 0x00000000ffc00000;
		tmp64 |= (userbuf[22] >> 42) & 0x00000000003fffff;
		/* OR sticky0 (bit 1430) to counter0 bit 32 */
		tmp64 |= (userbuf[22] >> 10) & 0x0000000080000000;
		raddr[0] = (uint32_t)tmp64;

		/* Counter1 is bits 1431 to 1462 */
		tmp64 =  (userbuf[22] >> 9) & 0x00000000ffffffff;
		/* OR sticky1 (bit 1463) to counter1 bit 32 */
		tmp64 |= (userbuf[22] << 23) & 0x0000000080000000;
		raddr[1] = (uint32_t)tmp64;

		/* Counter2 is bits 1464 to 1495 */
		tmp64 =  (userbuf[22] << 24) & 0x00000000ff000000;
		tmp64 |= (userbuf[23] >> 40) & 0x0000000000ffffff;
		/* OR sticky2 (bit 1496) to counter2 bit 32 */
		tmp64 |= (userbuf[23] >> 8) & 0x0000000080000000;
		raddr[2] = (uint32_t)tmp64;

		/* Counter3 is bits 1497 to 1528 */
		tmp64 =  (userbuf[23] >> 7) & 0x00000000ffffffff;
		/* OR sticky3 (bit 1529) to counter3 bit 32 */
		tmp64 |= (userbuf[23] << 25) & 0x0000000080000000;
		raddr[3] = (uint32_t)tmp64;

		/*
		 * Zero out the counters
		 */

		/*
		 * The counters and sticky-bits comprise the last 132 bits
		 * (1398 - 1529) of RDR16 on a U chip.  We'll zero these
		 * out the easy way: zero out last 10 bits of dword 21,
		 * all of dword 22 and 58 bits (plus 6 don't care bits) of
		 * dword 23.
		 */
		userbuf[21] &= 0xfffffffffffffc00ul;	/* 0 to last 10 bits */
		userbuf[22] = 0;
		userbuf[23] = 0;

		/*
		 * Write back the zeroed bytes + the image given
		 * the read was destructive.
		 */
		perf_rdr_write(16, userbuf);
	} else {

		/*
		 * Read RDR-15 which contains the counters and sticky bits
		 */
		if (!perf_rdr_read_ubuf(15, userbuf)) {
			return -13;
		}

		/*
		 * Clear out the counters
		 */
		perf_rdr_clear(15);

		/*
		 * Copy the counters 
		 */
		raddr[0] = (uint32_t)((userbuf[0] >> 32) & 0x00000000ffffffffUL);
		raddr[1] = (uint32_t)(userbuf[0] & 0x00000000ffffffffUL);
		raddr[2] = (uint32_t)((userbuf[1] >> 32) & 0x00000000ffffffffUL);
		raddr[3] = (uint32_t)(userbuf[1] & 0x00000000ffffffffUL);
	}

	return 0;
}