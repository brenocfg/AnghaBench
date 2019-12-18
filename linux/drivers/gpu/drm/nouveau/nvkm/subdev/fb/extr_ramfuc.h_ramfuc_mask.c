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
struct ramfuc_reg {int force; } ;
struct ramfuc {int dummy; } ;

/* Variables and functions */
 int ramfuc_rd32 (struct ramfuc*,struct ramfuc_reg*) ; 
 int /*<<< orphan*/  ramfuc_wr32 (struct ramfuc*,struct ramfuc_reg*,int) ; 

__attribute__((used)) static inline u32
ramfuc_mask(struct ramfuc *ram, struct ramfuc_reg *reg, u32 mask, u32 data)
{
	u32 temp = ramfuc_rd32(ram, reg);
	if (temp != ((temp & ~mask) | data) || reg->force) {
		ramfuc_wr32(ram, reg, (temp & ~mask) | data);
		reg->force = false;
	}
	return temp;
}