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
struct hinic_hwif {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HINIC_CSR_FUNC_ATTR0_ADDR ; 
 int /*<<< orphan*/  HINIC_CSR_FUNC_ATTR1_ADDR ; 
 int /*<<< orphan*/  hinic_hwif_read_reg (struct hinic_hwif*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_hwif_attr (struct hinic_hwif*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void read_hwif_attr(struct hinic_hwif *hwif)
{
	u32 addr, attr0, attr1;

	addr   = HINIC_CSR_FUNC_ATTR0_ADDR;
	attr0  = hinic_hwif_read_reg(hwif, addr);

	addr   = HINIC_CSR_FUNC_ATTR1_ADDR;
	attr1  = hinic_hwif_read_reg(hwif, addr);

	set_hwif_attr(hwif, attr0, attr1);
}