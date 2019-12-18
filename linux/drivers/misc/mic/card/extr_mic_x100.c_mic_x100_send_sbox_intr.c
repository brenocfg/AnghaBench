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
typedef  int u32 ;
struct mic_mw {int dummy; } ;

/* Variables and functions */
 scalar_t__ MIC_X100_SBOX_APICICR0 ; 
 scalar_t__ MIC_X100_SBOX_BASE_ADDRESS ; 
 int mic_mmio_read (struct mic_mw*,scalar_t__) ; 
 int /*<<< orphan*/  mic_mmio_write (struct mic_mw*,int,scalar_t__) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void mic_x100_send_sbox_intr(struct mic_mw *mw, int doorbell)
{
	u64 apic_icr_offset = MIC_X100_SBOX_APICICR0 + doorbell * 8;
	u32 apicicr_low = mic_mmio_read(mw, MIC_X100_SBOX_BASE_ADDRESS +
					apic_icr_offset);

	/* for MIC we need to make sure we "hit" the send_icr bit (13) */
	apicicr_low = (apicicr_low | (1 << 13));
	/*
	 * Ensure that the interrupt is ordered w.r.t. previous stores
	 * to main memory. Fence instructions are not implemented in X100
	 * since execution is in order but a compiler barrier is still
	 * required.
	 */
	wmb();
	mic_mmio_write(mw, apicicr_low,
		       MIC_X100_SBOX_BASE_ADDRESS + apic_icr_offset);
}