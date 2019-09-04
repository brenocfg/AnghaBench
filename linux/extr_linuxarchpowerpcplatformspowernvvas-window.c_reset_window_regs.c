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
struct vas_window {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMR ; 
 int /*<<< orphan*/  CURR_MSG_COUNT ; 
 int /*<<< orphan*/  FAULT_TX_WIN ; 
 int /*<<< orphan*/  HV_INTR_SRC_RA ; 
 int /*<<< orphan*/  LDATA_STAMP_CTL ; 
 int /*<<< orphan*/  LDMA_CACHE_CTL ; 
 int /*<<< orphan*/  LFIFO_BAR ; 
 int /*<<< orphan*/  LFIFO_SIZE ; 
 int /*<<< orphan*/  LNOTIFY_AFTER_COUNT ; 
 int /*<<< orphan*/  LNOTIFY_CTL ; 
 int /*<<< orphan*/  LNOTIFY_LPID ; 
 int /*<<< orphan*/  LNOTIFY_PID ; 
 int /*<<< orphan*/  LNOTIFY_SCOPE ; 
 int /*<<< orphan*/  LNOTIFY_TID ; 
 int /*<<< orphan*/  LPID ; 
 int /*<<< orphan*/  LRFIFO_PUSH ; 
 int /*<<< orphan*/  LRFIFO_WIN_PTR ; 
 int /*<<< orphan*/  LRX_WCRED ; 
 int /*<<< orphan*/  LRX_WCRED_ADDER ; 
 int /*<<< orphan*/  NX_UTIL_ADDER ; 
 int /*<<< orphan*/  OSU_INTR_SRC_RA ; 
 int /*<<< orphan*/  PID ; 
 int /*<<< orphan*/  PSWID ; 
 int /*<<< orphan*/  SEIDR ; 
 int /*<<< orphan*/  TX_RSVD_BUF_COUNT ; 
 int /*<<< orphan*/  TX_WCRED ; 
 int /*<<< orphan*/  TX_WCRED_ADDER ; 
 int /*<<< orphan*/  VREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WINCTL ; 
 int /*<<< orphan*/  WIN_CTX_CACHING_CTL ; 
 int /*<<< orphan*/  WIN_STATUS ; 
 int /*<<< orphan*/  XLATE_CTL ; 
 int /*<<< orphan*/  XLATE_LPCR ; 
 int /*<<< orphan*/  XLATE_MSR ; 
 int /*<<< orphan*/  write_hvwc_reg (struct vas_window*,int /*<<< orphan*/ ,unsigned long long) ; 

void reset_window_regs(struct vas_window *window)
{
	write_hvwc_reg(window, VREG(LPID), 0ULL);
	write_hvwc_reg(window, VREG(PID), 0ULL);
	write_hvwc_reg(window, VREG(XLATE_MSR), 0ULL);
	write_hvwc_reg(window, VREG(XLATE_LPCR), 0ULL);
	write_hvwc_reg(window, VREG(XLATE_CTL), 0ULL);
	write_hvwc_reg(window, VREG(AMR), 0ULL);
	write_hvwc_reg(window, VREG(SEIDR), 0ULL);
	write_hvwc_reg(window, VREG(FAULT_TX_WIN), 0ULL);
	write_hvwc_reg(window, VREG(OSU_INTR_SRC_RA), 0ULL);
	write_hvwc_reg(window, VREG(HV_INTR_SRC_RA), 0ULL);
	write_hvwc_reg(window, VREG(PSWID), 0ULL);
	write_hvwc_reg(window, VREG(LFIFO_BAR), 0ULL);
	write_hvwc_reg(window, VREG(LDATA_STAMP_CTL), 0ULL);
	write_hvwc_reg(window, VREG(LDMA_CACHE_CTL), 0ULL);
	write_hvwc_reg(window, VREG(LRFIFO_PUSH), 0ULL);
	write_hvwc_reg(window, VREG(CURR_MSG_COUNT), 0ULL);
	write_hvwc_reg(window, VREG(LNOTIFY_AFTER_COUNT), 0ULL);
	write_hvwc_reg(window, VREG(LRX_WCRED), 0ULL);
	write_hvwc_reg(window, VREG(LRX_WCRED_ADDER), 0ULL);
	write_hvwc_reg(window, VREG(TX_WCRED), 0ULL);
	write_hvwc_reg(window, VREG(TX_WCRED_ADDER), 0ULL);
	write_hvwc_reg(window, VREG(LFIFO_SIZE), 0ULL);
	write_hvwc_reg(window, VREG(WINCTL), 0ULL);
	write_hvwc_reg(window, VREG(WIN_STATUS), 0ULL);
	write_hvwc_reg(window, VREG(WIN_CTX_CACHING_CTL), 0ULL);
	write_hvwc_reg(window, VREG(TX_RSVD_BUF_COUNT), 0ULL);
	write_hvwc_reg(window, VREG(LRFIFO_WIN_PTR), 0ULL);
	write_hvwc_reg(window, VREG(LNOTIFY_CTL), 0ULL);
	write_hvwc_reg(window, VREG(LNOTIFY_PID), 0ULL);
	write_hvwc_reg(window, VREG(LNOTIFY_LPID), 0ULL);
	write_hvwc_reg(window, VREG(LNOTIFY_TID), 0ULL);
	write_hvwc_reg(window, VREG(LNOTIFY_SCOPE), 0ULL);
	write_hvwc_reg(window, VREG(NX_UTIL_ADDER), 0ULL);

	/* Skip read-only registers: NX_UTIL and NX_UTIL_SE */

	/*
	 * The send and receive window credit adder registers are also
	 * accessible from HVWC and have been initialized above. We don't
	 * need to initialize from the OS/User Window Context, so skip
	 * following calls:
	 *
	 *	write_uwc_reg(window, VREG(TX_WCRED_ADDER), 0ULL);
	 *	write_uwc_reg(window, VREG(LRX_WCRED_ADDER), 0ULL);
	 */
}