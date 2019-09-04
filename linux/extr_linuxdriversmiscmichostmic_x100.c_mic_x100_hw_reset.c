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
typedef  int u32 ;
struct mic_mw {int dummy; } ;
struct mic_device {struct mic_mw mmio; } ;

/* Variables and functions */
 int MIC_X100_SBOX_BASE_ADDRESS ; 
 int MIC_X100_SBOX_RGCR ; 
 int /*<<< orphan*/  mb () ; 
 int mic_mmio_read (struct mic_mw*,int) ; 
 int /*<<< orphan*/  mic_mmio_write (struct mic_mw*,int,int) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static void mic_x100_hw_reset(struct mic_device *mdev)
{
	u32 reset_reg;
	u32 rgcr = MIC_X100_SBOX_BASE_ADDRESS + MIC_X100_SBOX_RGCR;
	struct mic_mw *mw = &mdev->mmio;

	/* Ensure that the reset is ordered w.r.t. previous loads and stores */
	mb();
	/* Trigger reset */
	reset_reg = mic_mmio_read(mw, rgcr);
	reset_reg |= 0x1;
	mic_mmio_write(mw, reset_reg, rgcr);
	/*
	 * It seems we really want to delay at least 1 second
	 * after touching reset to prevent a lot of problems.
	 */
	msleep(1000);
}