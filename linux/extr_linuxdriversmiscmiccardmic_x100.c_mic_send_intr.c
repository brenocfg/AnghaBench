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
struct mic_device {struct mic_mw mmio; } ;

/* Variables and functions */
 int MIC_X100_MAX_DOORBELL_IDX ; 
 scalar_t__ MIC_X100_SBOX_BASE_ADDRESS ; 
 scalar_t__ MIC_X100_SBOX_SDBIC0 ; 
 int /*<<< orphan*/  MIC_X100_SBOX_SDBIC0_DBREQ_BIT ; 
 int /*<<< orphan*/  mic_mmio_write (struct mic_mw*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  wmb () ; 

void mic_send_intr(struct mic_device *mdev, int doorbell)
{
	struct mic_mw *mw = &mdev->mmio;

	if (doorbell > MIC_X100_MAX_DOORBELL_IDX)
		return;
	/* Ensure that the interrupt is ordered w.r.t previous stores. */
	wmb();
	mic_mmio_write(mw, MIC_X100_SBOX_SDBIC0_DBREQ_BIT,
		       MIC_X100_SBOX_BASE_ADDRESS +
		       (MIC_X100_SBOX_SDBIC0 + (4 * doorbell)));
}