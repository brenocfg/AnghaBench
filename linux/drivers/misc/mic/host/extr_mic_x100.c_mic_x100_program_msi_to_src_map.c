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
typedef  scalar_t__ u32 ;
struct mic_mw {int dummy; } ;
struct mic_device {struct mic_mw mmio; } ;

/* Variables and functions */
 scalar_t__ MIC_X100_SBOX_BASE_ADDRESS ; 
 scalar_t__ MIC_X100_SBOX_MXAR0 ; 
 int /*<<< orphan*/  __clear_bit (int,unsigned long*) ; 
 int /*<<< orphan*/  __set_bit (int,unsigned long*) ; 
 unsigned long mic_mmio_read (struct mic_mw*,scalar_t__) ; 
 int /*<<< orphan*/  mic_mmio_write (struct mic_mw*,unsigned long,scalar_t__) ; 

__attribute__((used)) static void
mic_x100_program_msi_to_src_map(struct mic_device *mdev,
				int idx, int offset, bool set)
{
	unsigned long reg;
	struct mic_mw *mw = &mdev->mmio;
	u32 mxar = MIC_X100_SBOX_BASE_ADDRESS +
		MIC_X100_SBOX_MXAR0 + idx * 4;

	reg = mic_mmio_read(mw, mxar);
	if (set)
		__set_bit(offset, &reg);
	else
		__clear_bit(offset, &reg);
	mic_mmio_write(mw, reg, mxar);
}