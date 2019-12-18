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
typedef  int u8 ;
struct controller {scalar_t__ hpc_reg; } ;

/* Variables and functions */
 scalar_t__ SLOT_ENABLE ; 
 int readb (scalar_t__) ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 

__attribute__((used)) static inline void slot_enable(struct controller *ctrl, u8 slot)
{
	u8 slot_enable;

	slot_enable = readb(ctrl->hpc_reg + SLOT_ENABLE);
	slot_enable |= (0x01 << slot);
	writeb(slot_enable, ctrl->hpc_reg + SLOT_ENABLE);
}