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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct hl_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WREG32_AND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WREG32_OR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void goya_mmu_prepare_reg(struct hl_device *hdev, u64 reg, u32 asid)
{
	/* mask to zero the MMBP and ASID bits */
	WREG32_AND(reg, ~0x7FF);
	WREG32_OR(reg, asid);
}