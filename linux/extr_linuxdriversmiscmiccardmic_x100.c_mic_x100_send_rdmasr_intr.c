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
struct mic_mw {int dummy; } ;

/* Variables and functions */
 scalar_t__ MIC_X100_SBOX_BASE_ADDRESS ; 
 int MIC_X100_SBOX_RDMASR0 ; 
 int /*<<< orphan*/  mic_mmio_write (struct mic_mw*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void mic_x100_send_rdmasr_intr(struct mic_mw *mw, int doorbell)
{
	int rdmasr_offset = MIC_X100_SBOX_RDMASR0 + (doorbell << 2);
	/*
	 * Ensure that the interrupt is ordered w.r.t. previous stores
	 * to main memory. Fence instructions are not implemented in X100
	 * since execution is in order but a compiler barrier is still
	 * required.
	 */
	wmb();
	mic_mmio_write(mw, 0, MIC_X100_SBOX_BASE_ADDRESS + rdmasr_offset);
}