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
typedef  int /*<<< orphan*/  u32 ;
struct mic_device {int /*<<< orphan*/  mmio; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ MIC_X100_SBOX_BASE_ADDRESS ; 
 scalar_t__ MIC_X100_SBOX_SPAD0 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  mic_mmio_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
mic_x100_write_spad(struct mic_device *mdev, unsigned int idx, u32 val)
{
	dev_dbg(&mdev->pdev->dev, "Writing 0x%x to scratch pad index %d\n",
		val, idx);
	mic_mmio_write(&mdev->mmio, val,
		       MIC_X100_SBOX_BASE_ADDRESS +
		       MIC_X100_SBOX_SPAD0 + idx * 4);
}