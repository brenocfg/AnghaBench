#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct mic_device {int /*<<< orphan*/  mmio; TYPE_2__* smpt; } ;
typedef  int dma_addr_t ;
struct TYPE_3__ {int page_shift; } ;
struct TYPE_4__ {TYPE_1__ info; } ;

/* Variables and functions */
 scalar_t__ MIC_X100_SBOX_BASE_ADDRESS ; 
 scalar_t__ MIC_X100_SBOX_SMPT00 ; 
 int /*<<< orphan*/  mic_mmio_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
mic_x100_smpt_set(struct mic_device *mdev, dma_addr_t dma_addr, u8 index)
{
#define SNOOP_ON	(0 << 0)
#define SNOOP_OFF	(1 << 0)
/*
 * Sbox Smpt Reg Bits:
 * Bits	31:2	Host address
 * Bits	1	RSVD
 * Bits	0	No snoop
 */
#define BUILD_SMPT(NO_SNOOP, HOST_ADDR)  \
	(u32)(((HOST_ADDR) << 2) | ((NO_SNOOP) & 0x01))

	uint32_t smpt_reg_val = BUILD_SMPT(SNOOP_ON,
			dma_addr >> mdev->smpt->info.page_shift);
	mic_mmio_write(&mdev->mmio, smpt_reg_val,
		       MIC_X100_SBOX_BASE_ADDRESS +
		       MIC_X100_SBOX_SMPT00 + (4 * index));
}