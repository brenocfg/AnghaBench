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
typedef  int u32 ;
struct mvs_info {int dummy; } ;

/* Variables and functions */
 int mvs_cr32 (struct mvs_info*,int) ; 
 int /*<<< orphan*/  mvs_cw32 (struct mvs_info*,int,int) ; 

__attribute__((used)) static void mvs_64xx_command_active(struct mvs_info *mvi, u32 slot_idx)
{
	u32 tmp;
	mvs_cw32(mvi, 0x40 + (slot_idx >> 3), 1 << (slot_idx % 32));
	mvs_cw32(mvi, 0x00 + (slot_idx >> 3), 1 << (slot_idx % 32));
	do {
		tmp = mvs_cr32(mvi, 0x00 + (slot_idx >> 3));
	} while (tmp & 1 << (slot_idx % 32));
	do {
		tmp = mvs_cr32(mvi, 0x40 + (slot_idx >> 3));
	} while (tmp & 1 << (slot_idx % 32));
}