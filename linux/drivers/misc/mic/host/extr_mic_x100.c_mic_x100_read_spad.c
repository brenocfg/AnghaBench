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
struct mic_device {TYPE_1__* pdev; int /*<<< orphan*/  mmio; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ MIC_X100_SBOX_BASE_ADDRESS ; 
 scalar_t__ MIC_X100_SBOX_SPAD0 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  mic_mmio_read (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static u32
mic_x100_read_spad(struct mic_device *mdev, unsigned int idx)
{
	u32 val = mic_mmio_read(&mdev->mmio,
		MIC_X100_SBOX_BASE_ADDRESS +
		MIC_X100_SBOX_SPAD0 + idx * 4);

	dev_dbg(&mdev->pdev->dev,
		"Reading 0x%x from scratch pad index %d\n", val, idx);
	return val;
}