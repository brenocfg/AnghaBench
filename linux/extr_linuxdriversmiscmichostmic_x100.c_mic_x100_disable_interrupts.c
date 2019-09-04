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
typedef  int u32 ;
struct mic_mw {int dummy; } ;
struct TYPE_2__ {int num_vectors; } ;
struct mic_device {TYPE_1__ irq_info; struct mic_mw mmio; } ;

/* Variables and functions */
 int MIC_X100_SBOX_BASE_ADDRESS ; 
 int MIC_X100_SBOX_DBR_BITS (int) ; 
 int MIC_X100_SBOX_DMA_BITS (int) ; 
 int MIC_X100_SBOX_SIAC0 ; 
 int MIC_X100_SBOX_SICC0 ; 
 int MIC_X100_SBOX_SICE0 ; 
 int mic_mmio_read (struct mic_mw*,int) ; 
 int /*<<< orphan*/  mic_mmio_write (struct mic_mw*,int,int) ; 

__attribute__((used)) static void mic_x100_disable_interrupts(struct mic_device *mdev)
{
	u32 reg;
	struct mic_mw *mw = &mdev->mmio;
	u32 sice0 = MIC_X100_SBOX_BASE_ADDRESS + MIC_X100_SBOX_SICE0;
	u32 siac0 = MIC_X100_SBOX_BASE_ADDRESS + MIC_X100_SBOX_SIAC0;
	u32 sicc0 = MIC_X100_SBOX_BASE_ADDRESS + MIC_X100_SBOX_SICC0;

	reg = mic_mmio_read(mw, sice0);
	mic_mmio_write(mw, reg, sicc0);

	if (mdev->irq_info.num_vectors > 1) {
		reg = mic_mmio_read(mw, siac0);
		reg &= ~(MIC_X100_SBOX_DBR_BITS(0xf) |
			MIC_X100_SBOX_DMA_BITS(0xff));
		mic_mmio_write(mw, reg, siac0);
	}
}