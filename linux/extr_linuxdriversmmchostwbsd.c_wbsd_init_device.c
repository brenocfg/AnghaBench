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
typedef  int u8 ;
struct wbsd_host {scalar_t__ base; int /*<<< orphan*/  flags; void* clk; } ;

/* Variables and functions */
 int WBSD_CARDPRESENT ; 
 scalar_t__ WBSD_CSR ; 
 int WBSD_DAT3_H ; 
 int WBSD_EINT_CARD ; 
 int WBSD_EINT_CRC ; 
 int WBSD_EINT_FIFO_THRE ; 
 int WBSD_EINT_TC ; 
 int WBSD_EINT_TIMEOUT ; 
 scalar_t__ WBSD_EIR ; 
 int /*<<< orphan*/  WBSD_FCARD_PRESENT ; 
 int WBSD_FIFO_RESET ; 
 int /*<<< orphan*/  WBSD_FIGNORE_DETECT ; 
 int /*<<< orphan*/  WBSD_IDX_CLK ; 
 int /*<<< orphan*/  WBSD_IDX_SETUP ; 
 int /*<<< orphan*/  WBSD_IDX_TAAC ; 
 scalar_t__ WBSD_ISR ; 
 int WBSD_POWER_N ; 
 int WBSD_SOFT_RESET ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 void* wbsd_read_index (struct wbsd_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wbsd_write_index (struct wbsd_host*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void wbsd_init_device(struct wbsd_host *host)
{
	u8 setup, ier;

	/*
	 * Reset chip (SD/MMC part) and fifo.
	 */
	setup = wbsd_read_index(host, WBSD_IDX_SETUP);
	setup |= WBSD_FIFO_RESET | WBSD_SOFT_RESET;
	wbsd_write_index(host, WBSD_IDX_SETUP, setup);

	/*
	 * Set DAT3 to input
	 */
	setup &= ~WBSD_DAT3_H;
	wbsd_write_index(host, WBSD_IDX_SETUP, setup);
	host->flags &= ~WBSD_FIGNORE_DETECT;

	/*
	 * Read back default clock.
	 */
	host->clk = wbsd_read_index(host, WBSD_IDX_CLK);

	/*
	 * Power down port.
	 */
	outb(WBSD_POWER_N, host->base + WBSD_CSR);

	/*
	 * Set maximum timeout.
	 */
	wbsd_write_index(host, WBSD_IDX_TAAC, 0x7F);

	/*
	 * Test for card presence
	 */
	if (inb(host->base + WBSD_CSR) & WBSD_CARDPRESENT)
		host->flags |= WBSD_FCARD_PRESENT;
	else
		host->flags &= ~WBSD_FCARD_PRESENT;

	/*
	 * Enable interesting interrupts.
	 */
	ier = 0;
	ier |= WBSD_EINT_CARD;
	ier |= WBSD_EINT_FIFO_THRE;
	ier |= WBSD_EINT_CRC;
	ier |= WBSD_EINT_TIMEOUT;
	ier |= WBSD_EINT_TC;

	outb(ier, host->base + WBSD_EIR);

	/*
	 * Clear interrupts.
	 */
	inb(host->base + WBSD_ISR);
}