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
typedef  int u64 ;
typedef  int u32 ;
struct hl_device {int dummy; } ;

/* Variables and functions */
 int CFG_BASE ; 
 int PROT_BITS_OFFS ; 
 int /*<<< orphan*/  WREG32 (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void goya_pb_set_block(struct hl_device *hdev, u64 base)
{
	u32 pb_addr = base - CFG_BASE + PROT_BITS_OFFS;

	while (pb_addr & 0xFFF) {
		WREG32(pb_addr, 0);
		pb_addr += 4;
	}
}