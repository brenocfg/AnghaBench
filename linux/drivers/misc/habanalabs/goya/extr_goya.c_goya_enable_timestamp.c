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
struct hl_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ CFG_BASE ; 
 int /*<<< orphan*/  WREG32 (scalar_t__,int) ; 
 scalar_t__ mmPSOC_TIMESTAMP_BASE ; 

__attribute__((used)) static void goya_enable_timestamp(struct hl_device *hdev)
{
	/* Disable the timestamp counter */
	WREG32(mmPSOC_TIMESTAMP_BASE - CFG_BASE, 0);

	/* Zero the lower/upper parts of the 64-bit counter */
	WREG32(mmPSOC_TIMESTAMP_BASE - CFG_BASE + 0xC, 0);
	WREG32(mmPSOC_TIMESTAMP_BASE - CFG_BASE + 0x8, 0);

	/* Enable the counter */
	WREG32(mmPSOC_TIMESTAMP_BASE - CFG_BASE, 1);
}