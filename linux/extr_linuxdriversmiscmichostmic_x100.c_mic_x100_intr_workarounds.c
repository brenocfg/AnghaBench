#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mic_mw {int dummy; } ;
struct mic_device {scalar_t__ stepping; TYPE_1__* intr_ops; struct mic_mw mmio; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* enable_interrupts ) (struct mic_device*) ;} ;

/* Variables and functions */
 scalar_t__ MIC_A0_STEP ; 
 scalar_t__ MIC_B0_STEP ; 
 scalar_t__ MIC_X100_SBOX_BASE_ADDRESS ; 
 scalar_t__ MIC_X100_SBOX_MSIXPBACR ; 
 int /*<<< orphan*/  mic_mmio_write (struct mic_mw*,int,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct mic_device*) ; 

__attribute__((used)) static void mic_x100_intr_workarounds(struct mic_device *mdev)
{
	struct mic_mw *mw = &mdev->mmio;

	/* Clear pending bit array. */
	if (MIC_A0_STEP == mdev->stepping)
		mic_mmio_write(mw, 1, MIC_X100_SBOX_BASE_ADDRESS +
			MIC_X100_SBOX_MSIXPBACR);

	if (mdev->stepping >= MIC_B0_STEP)
		mdev->intr_ops->enable_interrupts(mdev);
}