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
typedef  int /*<<< orphan*/  u32 ;
struct ssb_pcicore {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pcicore_read32 (struct ssb_pcicore*,int) ; 
 int /*<<< orphan*/  pcicore_write32 (struct ssb_pcicore*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 ssb_pcie_read(struct ssb_pcicore *pc, u32 address)
{
	pcicore_write32(pc, 0x130, address);
	return pcicore_read32(pc, 0x134);
}