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
struct gt215_ramfuc {int dummy; } ;
struct gt215_clk_info {int /*<<< orphan*/  pll; } ;

/* Variables and functions */
 int /*<<< orphan*/  ram_mask (struct gt215_ramfuc*,int,int,int) ; 
 int /*<<< orphan*/  ram_wait (struct gt215_ramfuc*,int,int,int,int) ; 
 int /*<<< orphan*/  ram_wr32 (struct gt215_ramfuc*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
gt215_ram_lock_pll(struct gt215_ramfuc *fuc, struct gt215_clk_info *mclk)
{
	ram_wr32(fuc, 0x004004, mclk->pll);
	ram_mask(fuc, 0x004000, 0x00000001, 0x00000001);
	ram_mask(fuc, 0x004000, 0x00000010, 0x00000000);
	ram_wait(fuc, 0x004000, 0x00020000, 0x00020000, 64000);
	ram_mask(fuc, 0x004000, 0x00000010, 0x00000010);
}